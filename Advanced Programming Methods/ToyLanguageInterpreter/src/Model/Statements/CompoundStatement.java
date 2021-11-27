package Model.Statements;

import Model.DataStructures.IADTStack;
import Model.Exceptions.StatementException;
import Model.Program.ProgramState;

public class CompoundStatement implements IStatement {
    private IStatement first;
    private IStatement second;

    public CompoundStatement(IStatement first, IStatement second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public ProgramState execute(ProgramState state) {
        IADTStack<IStatement> execution_stack = state.executionStack();
        execution_stack.push(second);
        execution_stack.push(first);
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new CompoundStatement(first, second);
    }

    @Override
    public String toString() {
        return '(' + first.toString() + "; " + second.toString() + ')';
    }
}
