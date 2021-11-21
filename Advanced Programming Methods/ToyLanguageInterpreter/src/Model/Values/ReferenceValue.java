package Model.Values;

import Model.Types.IType;
import Model.Types.ReferenceType;

public class ReferenceValue implements IValue {
    private int heap_address;
    private IType location_type;

    public ReferenceValue(int address, IType type) {
        this.heap_address = address;
        this.location_type = type;
    }

    @Override
    public IType getType() {
        return new ReferenceType(location_type);
    }

    public int getHeapAddress() {
        return heap_address;
    }

    public void setHeapAddress(int other) {
        heap_address = other;
    }

    @Override
    public IValue deepCopy() {
        return new ReferenceValue(heap_address, location_type);
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof ReferenceValue)
            return ((ReferenceValue) other).getHeapAddress() == heap_address && ((ReferenceValue) other).getType().equals(getType());
        return false;
    }

    @Override
    public String toString() {
        return String.format("(%d, %s)", heap_address, location_type.toString());
    }
}
