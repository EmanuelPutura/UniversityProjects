package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.StatementException;
import Model.Program.ProgramState;
import Model.Types.IType;

public class NOPStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new NOPStatement();
    }

    @Override
    public String toString() {
        return "no operation";
    }
}
