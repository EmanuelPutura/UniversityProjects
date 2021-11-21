package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;

import java.util.Map;

public interface IADTHeapDictionary extends IADTDictionary<Integer, IValue> {
    int put(IValue value) throws DictionaryException;
    int getFirstFreeLocation();
}
