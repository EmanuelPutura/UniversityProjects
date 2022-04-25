package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.ExpressionException;
import Model.Types.IType;
import Model.Values.IValue;

public class ValueExpression implements IExpression {
    private IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException {
        return value;
    }

    @Override
    public IType typeCheck(IADTDictionary<String, IType> type_env) throws ExpressionException {
        return value.getType();
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
