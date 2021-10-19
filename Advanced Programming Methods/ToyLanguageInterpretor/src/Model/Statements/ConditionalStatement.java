package Model.Statements;

import Model.DataStructures.IADTStack;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class ConditionalStatement implements IStatement {
    private IExpression expression;
    private IStatement then_statement;
    private IStatement else_statement;

    ConditionalStatement(IExpression expression, IStatement then_statement, IStatement else_statement) {
        this.expression = expression;
        this.then_statement = then_statement;
        this.else_statement = else_statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IADTStack<IStatement> execution_stack = state.executionStack();

        try {
            IValue condition = expression.eval(state.symbolsTable());
            if (condition.getType().equals(new BoolType())) {
                boolean condition_value = ((BoolValue) condition).getValue();
                if (condition_value)
                    execution_stack.push(then_statement);
                else
                    execution_stack.push(else_statement);
            }
            else
                throw new StatementException("Conditional expression must evaluate to a boolean value!");
        } catch (ExpressionException exception) {
            throw new StatementException(exception.getMessage());
        }
        return state;
    }

    @Override
    public String toString() {
        return String.format("IF (%s) THEN (%s) ELSE (%s)", expression.toString(), then_statement.toString(), else_statement.toString());
    }
}
