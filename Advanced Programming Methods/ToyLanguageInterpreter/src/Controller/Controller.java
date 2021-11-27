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
import java.util.stream.Collectors;

public class Controller {
    private IRepository repository;
    private String execution_logs;

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

    public void allStepsExecution(boolean display_logs) throws ControllerException, EmptyExecutionStackException {
        resetLogs();
        ProgramState program = null;
        try {
            program = repository.getCurrentProgram();
        } catch (RepositoryException exception) {
            throw new ControllerException(exception.getMessage());
        }

        allStepsExecution(program, display_logs);
    }

    public void allStepsExecution(ProgramState program, boolean display_logs) throws ControllerException, EmptyExecutionStackException {
        if (program == null)
            throw new ControllerException("Invalid program state!");

        resetLogs();

        IADTStack<IStatement> execution_stack = program.executionStack();
        if (execution_stack.empty())
            throw new EmptyExecutionStackException("Empty execution stack error!");

        try {
            repository.logProgramStateExec();
        } catch (RepositoryException error) {
            throw new ControllerException(error.getMessage());
        }

        StringBuilder string_builder = new StringBuilder(String.format("Initial program state: %s\n", program.toString()));

        while (!execution_stack.empty()) {
            oneStepExecution(program, false, false);
            try {
                repository.logProgramStateExec();
            } catch (RepositoryException error) {
                throw new ControllerException(error.getMessage());
            }
            string_builder.append(String.format("Current program state: %s\n", program.toString()));
        }

        execution_logs = string_builder.toString();
        if (display_logs)
            System.out.println(execution_logs);
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

    public int size() {
        return repository.size();
    }
}
