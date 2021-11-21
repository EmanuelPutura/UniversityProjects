package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.StringValue;

import java.util.*;

public class ADTDictionary<K, V> implements IADTDictionary<K, V> {
    protected HashMap<K, V> dictionary;

    public ADTDictionary() {
        dictionary = new HashMap<K, V>();
    }

    @Override
    public V get(K key) throws DictionaryException {
        try {
            return dictionary.get(key);
        } catch (Exception exception) {
            throw new DictionaryException(exception.getMessage());
        }
    }

    @Override
    public void put(K key, V value) throws DictionaryException {
        if (get(key) != null)
            throw new DictionaryException("The key is mapped to another value!");

        try {
            dictionary.put(key, value);
        } catch (Exception exception) {
            throw new DictionaryException(exception.getMessage());
        }
    }

    @Override
    public V remove(K key) throws DictionaryException {
        if (get(key) == null)
            throw new DictionaryException("The key was not found in the dictionary!");
        try {
            return dictionary.remove(key);
        } catch (Exception exception) {
            throw new DictionaryException(exception.getMessage());
        }
    }

    @Override
    public V replace(K key, V value) throws DictionaryException {
        if (get(key) == null)
            throw new DictionaryException("The key was not found in the dictionary!");
        try {
            return dictionary.replace(key, value);
        } catch (Exception exception) {
            throw new DictionaryException(exception.getMessage());
        }
    }

    @Override
    public boolean containsKey(K key) {
        return dictionary.containsKey(key);
    }

    @Override
    public String toString() {
        StringBuilder return_string = new StringBuilder("ADTDictionary: {");
        if (dictionary.isEmpty())
            return return_string.toString() + "}";

        int index = 0;
        for (Map.Entry<K, V> entry : dictionary.entrySet()) {
            if (index == 0)
                return_string.append(entry.getKey().toString()).append(": ").append(entry.getValue().toString());
            else
                return_string.append(", ").append(entry.getKey()).append(": ").append(entry.getValue().toString());
            index++;
        }

        return return_string.toString() + "}";
    }

    @Override
    public String toFileString(boolean print_values) {
        String type = "Symbols Table:\n";
        if (!print_values)
            type = "File Table:\n";
        StringBuilder return_string = new StringBuilder(type);
        if (dictionary.isEmpty())
            return return_string.toString() + "\n";

        for (Map.Entry<K, V> entry : dictionary.entrySet()) {
            return_string.append(entry.getKey().toString());
            if (print_values)
                return_string.append(" --> ").append(entry.getValue().toString()).append('\n');
            else
                return_string.append('\n');
        }

        return return_string.toString();
    }
}
