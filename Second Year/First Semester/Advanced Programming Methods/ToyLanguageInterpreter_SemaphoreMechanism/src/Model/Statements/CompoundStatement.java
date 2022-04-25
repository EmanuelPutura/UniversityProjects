package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTStack;
import Model.Exceptions.StatementException;
import Model.Program.ProgramState;
import Model.Types.IType;

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
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        return second.typeCheck(first.typeCheck(type_env));
    }

    @Override
    public IStatement deepCopy() {
        return new CompoundStatement(first, second);
    }

    @Override
    public String toString() {
//        return '(' + first.toString() + "; " + second.toString() + ')';
        return first.toString() + "; " + second.toString();
    }

    @Override
    public String toPresentationString() {
        return '(' + first.toString() + "; " + second.toString() + ')';
    }
}
