package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

public class ToyLockTable extends ToyDictionary<Integer, Integer> implements IADTLockTable {
    private int next_free_location;

    public ToyLockTable() {
        super();
        this.next_free_location = 1;
    }

    @Override
    public void put(Integer key, Integer value) throws DictionaryException {
        if (!key.equals(next_free_location))
            throw new DictionaryException("Invalid lock table location!");
        super.put(key, value);
        synchronized (this) {
            next_free_location++;
        }
    }

    @Override
    public int put(Integer value) throws DictionaryException {
        super.put(next_free_location, value);
        synchronized (this) {
            next_free_location++;
        }
        return next_free_location - 1;
    }

    @Override
    public int put() throws DictionaryException {
        return put(-1);
    }

    @Override
    public int getFirstFreeLocation() {
        int location_address = 1;
        while (this.dictionary.get(location_address) != null)
            location_address++;
        return location_address;
    }
}
