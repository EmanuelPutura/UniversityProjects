package Model.Statements;

import Model.DataStructures.IADTStack;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class WhileStatement implements IStatement {
    private IExpression while_expression;
    private IStatement statement;

    public WhileStatement(IExpression expression, IStatement statement) {
        this.while_expression = expression;
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTStack<IStatement> execution_stack = state.executionStack();
        IValue expression_value = null;

        try {
            expression_value = while_expression.eval(state.symbolsTable(), state.heapTable());
            if (!expression_value.getType().equals(new BoolType()))
                throw new StatementException("Expression in while statement should evaluate to bool!");

            BoolValue boolean_value = (BoolValue) expression_value;
            if (boolean_value.getValue()) {
                execution_stack.push(this);
                execution_stack.push(statement);
            }
        } catch (ExpressionException | DivisionByZeroException error) {
            throw new StatementException(error.getMessage());
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new WhileStatement(while_expression, statement);
    }

    @Override
    public String toString() {
        return String.format("while(%s) { %s }", while_expression.toString(), statement.toString());
    }
}
