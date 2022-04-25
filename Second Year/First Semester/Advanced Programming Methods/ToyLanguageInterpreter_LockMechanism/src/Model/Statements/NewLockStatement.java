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

public class NewLockStatement implements IStatement {
    private String variable_name;

    public NewLockStatement(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            int new_lock = state.lockTable().put();
            IValue variable = state.symbolsTable().get(variable_name);
            if (variable != null && variable.getType().equals(new IntType()))
                state.symbolsTable().replace(variable_name, new IntValue(new_lock));
            else throw new StatementException("Invalid variable type or name!");
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
        return new NewLockStatement(variable_name);
    }

    @Override
    public String toString() {
        return String.format("newLock(%s)", variable_name);
    }
}
