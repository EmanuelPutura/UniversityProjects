package Model.Statements;

import Model.Exceptions.StatementException;
import Model.Program.ProgramState;

public class NOPStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        return state;
    }

    @Override
    public String toString() {
        return "no operation";
    }
}
