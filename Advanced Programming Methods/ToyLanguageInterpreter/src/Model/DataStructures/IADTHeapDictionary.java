package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

public interface IADTHeapDictionary extends IADTDictionary<Integer, IValue> {
    void put(IValue value) throws DictionaryException;
    int getFirstFreeLocation();
}
