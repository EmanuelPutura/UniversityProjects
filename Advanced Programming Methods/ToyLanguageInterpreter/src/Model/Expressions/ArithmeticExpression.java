package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression implements IExpression {
    private IExpression left;
    private IExpression right;
    private char operator;  // can be '+', '-', '*' or '/'

    public ArithmeticExpression(IExpression left, IExpression right, char operator) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable) throws ExpressionException, DivisionByZeroException {
        IValue left_result, right_result;
        left_result = left.eval(symbolsTable);

        if (left_result.getType().equals(new IntType())) {
            right_result = right.eval(symbolsTable);
            if (right_result.getType().equals(new IntType())) {
                IntValue v1 = (IntValue) left_result, v2 = (IntValue) right_result;
                int no1 = v1.getValue(), no2 = v2.getValue();

                switch (operator) {
                    case '+':
                        return new IntValue(no1 + no2);
                    case '-':
                        return new IntValue(no1 - no2);
                    case '*':
                        return new IntValue(no1 * no2);
                    case '/':
                        if (no2 == 0)
                            throw new DivisionByZeroException("Division by zero!");
                        else
                            return new IntValue(no1 / no2);
                    default:
                        throw new ExpressionException("Invalid operator!");
                }
            }
            else
                throw new ExpressionException("Second operand is not an integer!");
        }
        else
            throw new ExpressionException("First operand is not an integer!");
    }

    @Override
    public IExpression deepCopy() {
        return new ArithmeticExpression(left, right, operator);
    }

    public char operator() {
        return operator;
    }

    @Override
    public String toString() {
        return left.toString() + ' ' + operator + ' ' + right.toString();
    }
}
