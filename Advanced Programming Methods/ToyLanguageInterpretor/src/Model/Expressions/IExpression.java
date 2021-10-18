package Model.Expressions;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.ExpressionException;
import Model.Values.IValue;

public interface IExpression {
    IValue eval(IADTDictionary<String, IValue> symbolsTable) throws ExpressionException;
}
