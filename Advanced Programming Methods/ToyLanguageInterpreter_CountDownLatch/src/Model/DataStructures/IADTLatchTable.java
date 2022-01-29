package Model.DataStructures;

import Model.Exceptions.DictionaryException;

public interface IADTLatchTable extends IADTDictionary<Integer, Integer> {
    int put(Integer value) throws DictionaryException;
    int getFirstFreeLocation();
}
