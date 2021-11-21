package Model.DataStructures;

import Model.Values.IValue;

public class ADTHeapDictionary extends ADTDictionary<Integer, IValue> {
    public ADTHeapDictionary() {
        super();
    }

    public int getFirstFreeLocation() {
        int location_address = 1;
        while (this.dictionary.get(location_address) != null)
            location_address++;
        return location_address;
    }
}
