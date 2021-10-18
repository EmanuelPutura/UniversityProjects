package Model.Types;

import Model.Values.IValue;
import Model.Values.IntValue;

public class IntType implements IType {
    @Override
    public IValue defaultValue() {
        return new IntValue(0);
    }

    @Override
    public boolean equals(Object other) {
        return other != null && other.getClass() == this.getClass();
    }

    @Override
    public String toString() {
        return "int";
    }
}
