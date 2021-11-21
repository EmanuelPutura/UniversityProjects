package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class HeapReadingExpression implements IExpression {
    private IExpression expression;

    public HeapReadingExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException, DivisionByZeroException {
        IValue expression_value = expression.eval(symbolsTable, heapTable);
        if (!(expression_value instanceof ReferenceValue))
            throw new ExpressionException(String.format("Expression '%s' must evaluate to a reference value!", expression.toString()));

        ReferenceValue reference = (ReferenceValue) expression_value;
        int heap_address = reference.getHeapAddress();

        if (!heapTable.containsKey(heap_address))
            throw new ExpressionException(String.format("Heap address '%d' is not valid!", heap_address));

        IValue value;
        try {
            value = heapTable.get(heap_address);
        } catch (DictionaryException error) {
            throw new ExpressionException(error.getMessage());
        }

        return value;
    }

    @Override
    public IExpression deepCopy() {
        return new HeapReadingExpression(expression);
    }

    @Override
    public String toString() {
        return String.format("readHeap(%s)", expression.toString());
    }
}
