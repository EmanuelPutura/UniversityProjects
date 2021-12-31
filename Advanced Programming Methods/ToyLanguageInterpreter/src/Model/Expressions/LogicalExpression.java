package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Types.BoolType;
import Model.Types.IType;
import Model.Types.IntType;
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
    public IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException, DivisionByZeroException {
        IValue left_result, right_result;
        left_result = left.eval(symbolsTable, heapTable);

        if (left_result.getType().equals(new BoolType())) {
            right_result = right.eval(symbolsTable, heapTable);
            if (right_result.getType().equals(new BoolType())) {
                BoolValue v1 = (BoolValue) left_result, v2 = (BoolValue) right_result;
                boolean b1 = v1.getValue(), b2 = v2.getValue();

                return switch (operator) {
                    case "&&" -> new BoolValue(b1 && b2);
                    case "||" -> new BoolValue(b1 || b2);
                    default -> throw new ExpressionException("Invalid operator!");
                };
            }
            else
                throw new ExpressionException("Second operand is not a boolean value!");
        }
        else
            throw new ExpressionException("First operand is not a boolean value!");
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> type_env) throws ExpressionException {
        IType type1 = left.typeCheck(type_env);
        IType type2 = right.typeCheck(type_env);

        if (type1.equals(new BoolType()))
            if (type2.equals(new BoolType()))
                return new BoolType();
            else throw new ExpressionException(String.format("The second operand of expression '%s' is not a boolean!", toString()));
        else throw new ExpressionException(String.format("The first operand of expression '%s' is not a boolean!", toString()));
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
