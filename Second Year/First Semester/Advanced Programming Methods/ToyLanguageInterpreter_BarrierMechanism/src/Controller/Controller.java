package Controller;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Program.ProgramState;
import Model.Values.IValue;
import Model.Values.ReferenceValue;
import Repository.IRepository;
import Repository.RepositoryException;

import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repository;
    private ExecutorService executor;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void addProgram(ProgramState program) {
        repository.addProgram(program);
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

    private void oneStepForAllPrograms(List<ProgramState> programs) throws ControllerException {
        // before the execution, print the ProgramState list into the log file

//        for (ProgramState program : programs) {
//            try {
//                repository.logProgramStateExec(program);
//            } catch (RepositoryException error) {
//                throw new ControllerException(error.getMessage());
//            }
//        }

        // run concurrently one step for each of the existing PrgStates
        // prepare the list of callables
        List<Callable<ProgramState>> call_list = programs.stream()
                .map((ProgramState program) -> (Callable<ProgramState>)(program::oneStepExecution))
                .collect(Collectors.toList());

        // start the execution of the callables
        // returns the list of newly created ProgramStates (namely threads)
        try {
//            if (executor == null)
//                executor = Executors.newFixedThreadPool(2);

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

    public void runOneStepForAllPrograms() throws ControllerException {
        executor = Executors.newFixedThreadPool(2);

        // remove the completed programs
        List<ProgramState> programs = removeCompletedPrograms(repository.getProgramStateList());
        if (programs.size() > 0) {
            // ------------------- safe garbage collector -------------------
            IADTHeapDictionary shared_heap = programs.get(0).heapTable();
            List<IADTDictionary<String, IValue>> all_symbols_tables = programs.stream()
                    .map(ProgramState::symbolsTable)
                    .collect(Collectors.toList());

            List<Integer> addresses_from_all_symbol_tables = new ArrayList<Integer>();
            all_symbols_tables.stream()
                    .map(table -> getAddressesFromSymbolsTable(table.getContent().values()))
                    .forEach(addresses_from_all_symbol_tables::addAll);

            shared_heap.setContent(safeGarbageCollector(
                    addresses_from_all_symbol_tables,
                    shared_heap.getContent()
            ));
            // --------------------------------------------------------------

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

    public void allStepsExecution() throws ControllerException {
        executor = Executors.newFixedThreadPool(2);

        // remove the completed programs
        List<ProgramState> programs = removeCompletedPrograms(repository.getProgramStateList());
        while (programs.size() > 0) {
            // ------------------- safe garbage collector -------------------
            IADTHeapDictionary shared_heap = programs.get(0).heapTable();
            List<IADTDictionary<String, IValue>> all_symbols_tables = programs.stream()
                    .map(ProgramState::symbolsTable)
                    .collect(Collectors.toList());

            List<Integer> addresses_from_all_symbol_tables = new ArrayList<Integer>();
            all_symbols_tables.stream()
                    .map(table -> getAddressesFromSymbolsTable(table.getContent().values()))
                    .forEach(addresses_from_all_symbol_tables::addAll);

            shared_heap.setContent(safeGarbageCollector(
                    addresses_from_all_symbol_tables,
                    shared_heap.getContent()
            ));
            // --------------------------------------------------------------

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

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> input_programs) {
        return input_programs.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public IRepository getRepository() {
        return this.repository;
    }
}
