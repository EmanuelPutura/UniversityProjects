package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import javafx.util.Pair;

import java.util.List;

public class ToyBarrierTable extends ToyDictionary<Integer, Pair<Integer, List<Integer>>> implements IADTBarrierTable {
    private int next_free_location;

    public ToyBarrierTable() {
        super();
        this.next_free_location = 1;
    }

    @Override
    public void put(Integer key, Pair<Integer, List<Integer>> value) throws DictionaryException {
        if (!key.equals(next_free_location))
            throw new DictionaryException("Invalid lock table location!");
        super.put(key, value);
        synchronized (this) {
            next_free_location++;
        }
    }

    @Override
    public int put(Pair<Integer, List<Integer>> value) throws DictionaryException {
        super.put(next_free_location, value);
        synchronized (this) {
            next_free_location++;
        }
        return next_free_location - 1;
    }

    @Override
    public int getFirstFreeLocation() {
        int location_address = 1;
        while (this.dictionary.get(location_address) != null)
            location_address++;
        return location_address;
    }
}
