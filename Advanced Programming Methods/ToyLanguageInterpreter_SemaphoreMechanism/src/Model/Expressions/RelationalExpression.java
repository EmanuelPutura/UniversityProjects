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
import Model.Values.IntValue;

public class RelationalExpression implements IExpression {
    private IExpression left;
    private IExpression right;
    private String operator;  // can be '<', '>', '<=', '>=', '!=', '=='

    public RelationalExpression(IExpression left, IExpression right, String operator) {
        this.left = left;
        this.right = right;
        this.operator = operator;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException, DivisionByZeroException {
        IValue left_result, right_result;
        left_result = left.eval(symbolsTable, heapTable);
        if (!left_result.getType().equals(new IntType()))
            throw new ExpressionException("First operand is not an integer!");

        right_result = right.eval(symbolsTable, heapTable);
        if (!right_result.getType().equals(new IntType()))
            throw new ExpressionException("Second operand is not an integer.");

        IntValue v1 = (IntValue) left_result, v2 = (IntValue) right_result;
        int no1 = v1.getValue(), no2 = v2.getValue();

        return switch (operator) {
            case "<" -> new BoolValue(no1 < no2);
            case "<=" -> new BoolValue(no1 <= no2);
            case ">" -> new BoolValue(no1 > no2);
            case ">=" -> new BoolValue(no1 >= no2);
            case "==" -> new BoolValue(no1 == no2);
            case "!=" -> new BoolValue(no1 != no2);
            default -> throw new ExpressionException("Invalid operator!");
        };

    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> type_env) throws ExpressionException {
        IType type1 = left.typeCheck(type_env);
        IType type2 = right.typeCheck(type_env);

        if (type1.equals(new IntType()))
            if (type2.equals(new IntType()))
                return new BoolType();
            else throw new ExpressionException(String.format("The second operand of expression '%s' is not an integer!", toString()));
        else throw new ExpressionException(String.format("The first operand of expression '%s' is not an integer!", toString()));
    }

    @Override
    public IExpression deepCopy() {
        return new RelationalExpression(left, right, operator);
    }

    @Override
    public String toString() {
        return left.toString() + ' ' + operator + ' ' + right.toString();
    }
}
