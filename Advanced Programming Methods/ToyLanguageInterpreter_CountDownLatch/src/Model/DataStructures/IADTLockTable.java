package Model.DataStructures;

import Model.Exceptions.DictionaryException;

public interface IADTLockTable extends IADTDictionary<Integer, Integer> {
    int put(Integer value) throws DictionaryException;
    int put() throws DictionaryException;
    int getFirstFreeLocation();
}
