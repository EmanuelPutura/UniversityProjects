package Model.Statements;

import Model.Exceptions.StatementException;
import Model.Program.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementException;
}
