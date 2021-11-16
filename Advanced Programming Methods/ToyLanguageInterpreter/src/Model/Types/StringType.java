package Model.Types;

import Model.Values.IValue;
import Model.Values.StringValue;

public class StringType implements IType {
    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }

    @Override
    public boolean equals(Object other) {
        return other != null && other.getClass() == this.getClass();
    }

    @Override
    public String toString() {
        return "string";
    }
}
