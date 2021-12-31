package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTList;
import Model.DataStructures.IADTStack;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class PrintStatement implements IStatement {
    private IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IADTList<IValue> out_list = state.outList();
        try {
            out_list.add(expression.eval(state.symbolsTable(), state.heapTable()));
        } catch (ExpressionException | DivisionByZeroException exception) {
            throw new StatementException(exception.getMessage());
        }
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            expression.typeCheck(type_env);
            return type_env;
        } catch (ExpressionException e) {
            throw new StatementException(e.getMessage());
        }

    }

    @Override
    public IStatement deepCopy() {
        return new PrintStatement(expression);
    }

    @Override
    public String toString() {
        return String.format("print(%s)", expression.toString());
    }
}
