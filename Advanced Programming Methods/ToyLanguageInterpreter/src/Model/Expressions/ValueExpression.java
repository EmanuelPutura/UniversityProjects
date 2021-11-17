package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.ExpressionException;
import Model.Values.IValue;

public class ValueExpression implements IExpression {
    private IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable) throws ExpressionException {
        return value;
    }

    @Override
    public IExpression deepCopy() {
        return new ValueExpression(value);
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
