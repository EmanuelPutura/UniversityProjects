package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.StackException;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Types.IType;

public class FunctionReturnStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            state.allSymbolTables().pop();
        } catch (StackException e) {
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new FunctionReturnStatement();
    }

    @Override
    public String toString() {
        return "return";
    }
}
