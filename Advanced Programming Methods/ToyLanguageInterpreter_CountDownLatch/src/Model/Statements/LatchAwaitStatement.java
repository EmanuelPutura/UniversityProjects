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

public class LatchAwaitStatement implements IStatement {
    private String variable_name;

    public LatchAwaitStatement(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue var_value = state.symbolsTable().get(variable_name);
            if (var_value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!var_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should be of integer type!", variable_name));

            Integer latch_location = ((IntValue) var_value).getValue();
            Integer latch_value = state.latchTable().get(latch_location);

            if (latch_value == null)
                throw new StatementException("Invalid latch table location!");
            if (latch_value != 0)
                state.executionStack().push(this);

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
                throw new StatementException(String.format("Variable '%s' should be of integer type!", variable_name));
        } catch (DictionaryException e) {
            throw new StatementException(e.getMessage());
        }

        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new LatchAwaitStatement(variable_name);
    }

    @Override
    public String toString() {
        return String.format("latchAwait(%s)", variable_name);
    }
}
