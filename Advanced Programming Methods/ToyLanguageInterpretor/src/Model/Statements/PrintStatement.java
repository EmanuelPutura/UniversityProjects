package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTList;
import Model.DataStructures.IADTStack;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
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
            out_list.add(expression.eval(state.symbolsTable()));
        } catch (ExpressionException exception) {
            throw new StatementException(exception.getMessage());
        }
        return state;
    }

    @Override
    public String toString() {
        return String.format("print(%s)", expression.toString());
    }
}
