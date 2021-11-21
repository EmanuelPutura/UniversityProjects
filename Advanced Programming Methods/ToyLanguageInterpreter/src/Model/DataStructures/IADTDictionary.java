package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.StringValue;

public interface IADTDictionary<K, V> {
    V get(K key) throws DictionaryException;
    void put(K key, V value) throws DictionaryException;
    V remove(K key) throws DictionaryException;
    V replace(K key, V value) throws DictionaryException;
    boolean containsKey(K key);

    String toString();
    String toFileString(int dictionary_type) throws DictionaryException;
}
