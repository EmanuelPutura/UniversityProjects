package Model.Statements;

import Model.DataStructures.ToyStack;
import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTStack;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Types.IType;

public class ForkStatement implements IStatement {
    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTStack<IStatement> new_execution_stack = new ToyStack<IStatement>();
        return new ProgramState(new_execution_stack, state.symbolsTable().deepCopy(), state.outList(), state.fileTable(), state.heapTable(), state.lockTable(), statement);
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        statement.typeCheck(type_env.deepCopy());
        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new ForkStatement(statement);
    }

    @Override
    public String toString() {
        return String.format("fork(%s)", statement.toString());
    }
}
