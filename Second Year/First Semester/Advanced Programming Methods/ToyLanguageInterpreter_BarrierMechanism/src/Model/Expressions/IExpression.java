package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.DivisionByZeroException;
import Model.Exceptions.ExpressionException;
import Model.Types.IType;
import Model.Values.IValue;

public interface IExpression {
    IValue eval(IADTDictionary<String, IValue> symbolsTable, IADTHeapDictionary heapTable) throws ExpressionException, DivisionByZeroException;
    IType typeCheck(IADTDictionary<String, IType> type_env) throws ExpressionException;
    IExpression deepCopy();
}
