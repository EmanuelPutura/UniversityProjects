package Model.Types;

import Model.Values.IValue;
import Model.Values.ReferenceValue;

public class ReferenceType implements IType {
    private IType location_type;

    public ReferenceType(IType location_type) {
        this.location_type = location_type;
    }

    public IType getLocationType() {
        return location_type;
    }

    @Override
    public IValue defaultValue() {
        return new ReferenceValue(0, location_type);
    }

    @Override
    public IType deepCopy() {
        return new ReferenceType(location_type);
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof ReferenceType)
            return location_type.equals(((ReferenceType) other).getLocationType());
        return false;
    }

    @Override
    public String toString() {
        return "Ref(" + location_type.toString() + ")";
    }
}
