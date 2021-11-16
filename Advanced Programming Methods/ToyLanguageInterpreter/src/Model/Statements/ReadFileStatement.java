package Model.Statements;

import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;

public class ReadFileStatement implements IStatement {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        return null;
    }
}
