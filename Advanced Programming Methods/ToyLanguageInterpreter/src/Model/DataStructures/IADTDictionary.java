package Model.DataStructures;

import Model.Exceptions.DictionaryException;

public interface IADTDictionary<K, V> {
    V get(K key) throws DictionaryException;
    void put(K key, V value) throws DictionaryException;
    V remove(K key) throws DictionaryException;
    V search(K key) throws DictionaryException;
    V replace(K key, V value) throws DictionaryException;
    String toString();
    String toFileString(boolean print_values);
}
