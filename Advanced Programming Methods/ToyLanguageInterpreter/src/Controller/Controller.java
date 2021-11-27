package Controller;

import Model.DataStructures.IADTStack;
import Model.Exceptions.*;
import Model.Program.ProgramState;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Model.Values.ReferenceValue;
import Repository.IRepository;
import Repository.RepositoryException;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repository;
    private String execution_logs;
    private ExecutorService executor;

    public Controller(IRepository repository) {
        this.repository = repository;
        this.execution_logs = "";
    }

    public void addProgram(ProgramState program) {
        repository.addProgram(program);
        this.execution_logs = "";
    }

    public String logs() {
        return execution_logs;
    }

    private void resetLogs() {
        execution_logs = "";
    }

    private List<Integer> getAddressesFromSymbolsTable(Collection<IValue> symbols_table_values) {
        return symbols_table_values.stream()
                .filter(value -> value instanceof ReferenceValue)
                .map(value -> ((ReferenceValue) value).getHeapAddress())
                .collect(Collectors.toList());
    }

    private List<Integer> getAddressesReferencedByHeapVariables(Collection<IValue> heap_table_values) {
        return heap_table_values.stream()
                .filter(value -> value instanceof ReferenceValue)
                .map(value -> ((ReferenceValue) value).getHeapAddress())
                .collect(Collectors.toList());
    }

    private Map<Integer, IValue> unsafeGarbageCollector(List<Integer> symbols_table_addresses, Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(dict_elem -> symbols_table_addresses.contains(dict_elem.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private Map<Integer, IValue> safeGarbageCollector(List<Integer> symbols_table_addresses, Map<Integer, IValue> heap) {
        List<Integer> addresses_referenced_from_heap = getAddressesReferencedByHeapVariables(heap.values());
        return heap.entrySet().stream()
                .filter(dict_elem -> (symbols_table_addresses.contains(dict_elem.getKey()) || addresses_referenced_from_heap.contains(dict_elem.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public ProgramState oneStepExecution(boolean reset_logs, boolean display_logs) throws ControllerException, EmptyExecutionStackException {
        if (reset_logs)
            resetLogs();

        ProgramState program = null;
        try {
            program = repository.getCurrentProgram();
        } catch (RepositoryException exception) {
            throw new ControllerException(exception.getMessage());
        }

        return oneStepExecution(program, reset_logs, display_logs);
    }

    public ProgramState
    oneStepExecution(ProgramState program, boolean reset_logs, boolean display_logs) throws ControllerException, EmptyExecutionStackException {
        if (program == null)
            throw new ControllerException("Invalid program state!");
        if (reset_logs)
            resetLogs();

        IADTStack<IStatement> execution_stack = program.executionStack();
        if (execution_stack.empty())
            throw new EmptyExecutionStackException("Empty execution stack error!");

        execution_logs = String.format("Initial program state: %s\n", program.toString());
        IStatement to_execute;

        try {
            to_execute = execution_stack.pop();
        } catch (StackException exception) {
            throw new ControllerException(exception.getMessage());
        }

        try {
            ProgramState return_state = to_execute.execute(program);
            execution_logs += String.format("Current program state: %s", return_state.toString());

            if (display_logs)
                System.out.println(execution_logs);

            return_state.heapTable().setContent(safeGarbageCollector(
                    getAddressesFromSymbolsTable(return_state.symbolsTable().getContent().values()),
                    return_state.heapTable().getContent()
            ));

            return return_state;
        } catch (StatementException | UndeclaredVariableException exception) {
            throw new ControllerException(exception.getMessage());
        }
    }

    public void setAndSwapCurrentProgram(int new_index) throws InvalidIndexException, ControllerException {
        try {
            ProgramState current_program = repository.getCurrentProgram();
            if (new_index < 0 || new_index >= repository.size())
                throw new InvalidIndexException("Index out of bounds!");

            repository.setCurrentProgram(repository.getProgramStateList().get(new_index));
            repository.getProgramStateList().set(new_index, current_program);
        } catch (RepositoryException exception) {
            throw new ControllerException(exception.getMessage());
        }
    }

    public List<ProgramState> getAllProgramStates() {
        return repository.getProgramStateList();
    }

    public void oneStepForAllPrograms(List<ProgramState> programs) throws ControllerException {
        // before the execution, print the ProgramState list into the log file
        for (ProgramState program : programs) {
            try {
                repository.logProgramStateExec(program);
            } catch (RepositoryException error) {
                throw new ControllerException(error.getMessage());
            }
        }

        // run concurrently one step for each of the existing PrgStates
        // prepare the list of callables
        List<Callable<ProgramState>> call_list = programs.stream()
                .map((ProgramState program) -> (Callable<ProgramState>)(program::oneStepExecution))
                .collect(Collectors.toList());

        // start the execution of the callables
        // returns the lis of newly created ProgramStates (namely threads)
        try {
            List<ProgramState> new_programs_list = executor.invokeAll(call_list).stream()
                    .map(future -> {
                        try {
                            return future.get();
                        } catch (ExecutionException | InterruptedException error) {
                            System.out.println(error.getMessage());
                        }
                        return null;
                    })
                    .filter(Objects::nonNull)
                    .collect(Collectors.toList());

            // add the new created threads to the list of existing threads
            programs.addAll(new_programs_list);

            // after the execution, print the ProgramStates list into the log file
            for (ProgramState program : programs) {
                try {
                    repository.logProgramStateExec(program);
                } catch (RepositoryException error) {
                    throw new ControllerException(error.getMessage());
                }
            }

            // save the current programs into the repository
            repository.setProgramStateList(programs);
        } catch (InterruptedException ignored) {
        }

    }

    public void allStepsExecution() throws ControllerException {
        executor = Executors.newFixedThreadPool(2);

        // remove the completed programs
        List<ProgramState> programs = removeCompletedPrograms(repository.getProgramStateList());
        while (programs.size() > 0) {
            oneStepForAllPrograms(programs);

            // remove the completed programs
            programs = removeCompletedPrograms(repository.getProgramStateList());
        }

        executor.shutdownNow();
        // here the repository still contains at least one completed program
        // and its List<ProgramState> is not empty. Note that oneStepForAllPrograms(...)
        // calls the method setProgramStateList(...) of repository in order to change the repository

        // update the repository state
        repository.setProgramStateList(programs);
    }

    List<ProgramState> removeCompletedPrograms(List<ProgramState> input_programs) {
        return input_programs.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public int size() {
        return repository.size();
    }
}
