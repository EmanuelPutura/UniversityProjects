package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

public class ADTHeapDictionary extends ADTDictionary<Integer, IValue> implements IADTHeapDictionary {
    public ADTHeapDictionary() {
        super();
    }

    @Override
    public void put(Integer key, IValue value) throws DictionaryException {
        if (!key.equals(getFirstFreeLocation()))
            throw new DictionaryException("Invalid heap location!");
        super.put(key, value);
    }

    @Override
    public void put(IValue value) throws DictionaryException {
        super.put(getFirstFreeLocation(), value);
    }

    public int getFirstFreeLocation() {
        int location_address = 1;
        while (this.dictionary.get(location_address) != null)
            location_address++;
        return location_address;
    }
}
