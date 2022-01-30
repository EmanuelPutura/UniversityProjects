package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import javafx.util.Pair;

import java.util.List;

public interface IADTSemaphoreTable extends IADTDictionary<Integer, Pair<Integer, List<Integer>>> {
    int put(Pair<Integer, List<Integer>> value) throws DictionaryException;
    int getFirstFreeLocation();
}
