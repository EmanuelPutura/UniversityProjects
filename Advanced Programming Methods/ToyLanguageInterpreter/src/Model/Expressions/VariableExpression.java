package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.ExpressionException;
import Model.Values.IValue;

public class VariableExpression implements IExpression {
    String label;

    public VariableExpression(String label) {
        this.label = label;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException {
        try {
            return symbolsTable.get(label);
        } catch (DictionaryException exception) {
            throw new ExpressionException(exception.getMessage());
        }
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(label);
    }

    @Override
    public String toString() {
        return label;
    }
}
