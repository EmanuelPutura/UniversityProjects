package Model.Types;

import Model.Values.IValue;

public interface IType {
    IValue defaultValue();
    IType deepCopy();
}
