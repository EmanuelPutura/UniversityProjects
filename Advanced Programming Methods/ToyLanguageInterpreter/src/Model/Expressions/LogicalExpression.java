package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class LogicalExpression implements IExpression {
    private IExpression left;
    private IExpression right;
    private String operator;

    LogicalExpression(IExpression left, IExpression right, String operator) {
        this.left = left;
        this.right = right;
        this.operator = operator;  // can be '&&' or '||'
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable) throws ExpressionException, DivisionByZeroException {
        IValue left_result, right_result;
        left_result = left.eval(symbolsTable);

        if (left_result.getType().equals(new BoolType())) {
            right_result = right.eval(symbolsTable);
            if (right_result.getType().equals(new BoolType())) {
                BoolValue v1 = (BoolValue) left_result, v2 = (BoolValue) right_result;
                boolean b1 = v1.getValue(), b2 = v2.getValue();

                switch (operator) {
                    case "&&":
                        return new BoolValue(b1 && b2);
                    case "||":
                        return new BoolValue(b1 || b2);
                    default:
                        throw new ExpressionException("Invalid operator!");
                }
            }
            else
                throw new ExpressionException("Second operand is not a boolean value!");
        }
        else
            throw new ExpressionException("First operand is not a boolean value!");
    }

    @Override
    public IExpression deepCopy() {
        return new LogicalExpression(left, right, operator);
    }

    @Override
    public String toString() {
        return left.toString() + ' ' + operator + ' ' + right.toString();
    }
}
