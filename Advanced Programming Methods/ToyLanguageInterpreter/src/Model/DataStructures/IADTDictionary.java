package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.util.Map;

public interface IADTDictionary<K, V> {
    V get(K key) throws DictionaryException;
    void put(K key, V value) throws DictionaryException;
    V remove(K key) throws DictionaryException;
    V replace(K key, V value) throws DictionaryException;
    boolean containsKey(K key);

    Map<K, V> getContent();
    void setContent(Map<K, V> other);

    String toString();
    String toFileString(int dictionary_type);
}
