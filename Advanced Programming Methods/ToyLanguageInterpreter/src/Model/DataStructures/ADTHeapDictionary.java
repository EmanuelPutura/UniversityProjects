package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

import java.util.Map;

public class ADTHeapDictionary extends ADTDictionary<Integer, IValue> implements IADTHeapDictionary {
    private int next_free_location;

    public ADTHeapDictionary() {
        super();
        this.next_free_location = 1;
    }

    @Override
    public void put(Integer key, IValue value) throws DictionaryException {
        if (!key.equals(next_free_location))
            throw new DictionaryException("Invalid heap location!");
        super.put(key, value);
        next_free_location++;
    }

    @Override
    public int put(IValue value) throws DictionaryException {
        super.put(getFirstFreeLocation(), value);
        next_free_location++;
        return next_free_location - 1;
    }

    public int getFirstFreeLocation() {
        int location_address = 1;
        boolean found = false;

        while (this.dictionary.get(location_address) != null) {
            location_address++;
            found = true;
        }
        if (!found)
            return -1;
        return location_address;
    }
}
