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

public class UnlockStatement implements IStatement {
    private String variable_name;

    public UnlockStatement(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue value = state.symbolsTable().get(variable_name);
            if (value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' must be of integer type!", variable_name));

            int found_index = ((IntValue) value).getValue();
            Integer current_program = state.lockTable().get(found_index);
            if (current_program == null)
                throw new StatementException("Invalid lock!");

            if (current_program == state.programID())
                state.lockTable().replace(found_index, -1);
        } catch (DictionaryException error) {
            throw new StatementException(error.getMessage());
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
                throw new StatementException(String.format("Variable '%s' must be of integer type!", variable_name));
            return type_env;
        } catch (DictionaryException e) {
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public IStatement deepCopy() {
        return new UnlockStatement(variable_name);
    }

    @Override
    public String toString() {
        return String.format("unlock(%s)", variable_name);
    }
}
