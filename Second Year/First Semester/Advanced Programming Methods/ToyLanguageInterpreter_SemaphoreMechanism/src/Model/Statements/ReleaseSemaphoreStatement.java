package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class ReleaseSemaphoreStatement implements IStatement {
    private String variable_name;

    public ReleaseSemaphoreStatement(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue variable_value = state.symbolsTable().get(variable_name);
            if (variable_value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!variable_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should have integer type!", variable_name));

            int semaphore_location = ((IntValue) variable_value).getValue();
            Pair<Integer, List<Integer>> semaphore_entry = state.semaphoreTable().get(semaphore_location);
            if (semaphore_entry == null)
                throw new StatementException("Invalid semaphore location!");

            Integer semaphore_n = semaphore_entry.getKey();
            List<Integer> acquired_programs = semaphore_entry.getValue();

            Integer program_id = state.programID();
            if (acquired_programs.contains(program_id))
               acquired_programs.remove(program_id);
        } catch (DictionaryException e) {
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            IType var_type = type_env.get(variable_name);
            if (var_type == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!var_type.equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should have integer type!", variable_name));
        } catch (DictionaryException e) {
            throw new StatementException(e.getMessage());
        }

        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new ReleaseSemaphoreStatement(variable_name);
    }

    @Override
    public String toString() {
        return String.format("releaseSemaphore(%s)", variable_name);
    }
}
