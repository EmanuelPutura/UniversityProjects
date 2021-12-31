package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTStack;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Values.BoolValue;
import Model.Values.IValue;

import javax.swing.plaf.nimbus.State;

public class ConditionalStatement implements IStatement {
    private IExpression expression;
    private IStatement then_statement;
    private IStatement else_statement;

    public ConditionalStatement(IExpression expression, IStatement then_statement, IStatement else_statement) {
        this.expression = expression;
        this.then_statement = then_statement;
        this.else_statement = else_statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IADTStack<IStatement> execution_stack = state.executionStack();

        try {
            IValue condition = expression.eval(state.symbolsTable(), state.heapTable());
            if (condition.getType().equals(new BoolType())) {
                boolean condition_value = ((BoolValue) condition).getValue();
                if (condition_value)
                    execution_stack.push(then_statement);
                else
                    execution_stack.push(else_statement);
            }
            else
                throw new StatementException("Conditional expression must evaluate to a boolean value!");
        } catch (ExpressionException | DivisionByZeroException exception) {
            throw new StatementException(exception.getMessage());
        }
        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            IType exp_type = expression.typeCheck(type_env);
            if (!exp_type.equals(new BoolType()))
                throw new StatementException(String.format("The if condition from the statement '%s' must have boolean type!", toString()));
            then_statement.typeCheck(type_env.deepCopy());
            else_statement.typeCheck(type_env.deepCopy());
            return type_env;
        } catch (ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public IStatement deepCopy() {
        return new ConditionalStatement(expression, then_statement, else_statement);
    }

    @Override
    public String toString() {
        return String.format("IF (%s) THEN (%s) ELSE (%s)", expression.toString(), then_statement.toString(), else_statement.toString());
    }
}
