package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

public class ToyHeapDictionary extends ToyDictionary<Integer, IValue> implements IADTHeapDictionary {
    private int next_free_location;

    public ToyHeapDictionary() {
        super();
        this.next_free_location = 1;
    }

    @Override
    public void put(Integer key, IValue value) throws DictionaryException {
        if (!key.equals(next_free_location))
            throw new DictionaryException("Invalid heap location!");
        super.put(key, value);
        synchronized (this) {
            next_free_location++;
        }
    }

    @Override
    public int put(IValue value) throws DictionaryException {
        super.put(next_free_location, value);
        synchronized (this) {
            next_free_location++;
        }
        return next_free_location - 1;
    }

    public int getFirstFreeLocation() {
        int location_address = 1;
        while (this.dictionary.get(location_address) != null)
            location_address++;
        return location_address;
    }
}
