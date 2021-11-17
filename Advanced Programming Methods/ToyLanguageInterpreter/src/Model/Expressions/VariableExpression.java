package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.ExpressionException;
import Model.Values.IValue;

public class VariableExpression implements IExpression {
    String label;

    public VariableExpression(String label) {
        this.label = label;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable) throws ExpressionException {
        try {
            return symbolsTable.search(label);
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
