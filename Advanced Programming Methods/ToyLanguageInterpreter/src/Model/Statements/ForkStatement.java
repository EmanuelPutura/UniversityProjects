package Model.Statements;

import Model.DataStructures.ADTStack;
import Model.DataStructures.IADTStack;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;

public class ForkStatement implements IStatement {
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTStack<IStatement> new_execution_stack = new ADTStack<IStatement>();
        return new ProgramState(new_execution_stack, state.symbolsTable(), state.outList(), state.fileTable(), state.heapTable(), statement);
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(statement);
    }

//    @Override
//    public String toString() {
//        return "";
//    }
}
