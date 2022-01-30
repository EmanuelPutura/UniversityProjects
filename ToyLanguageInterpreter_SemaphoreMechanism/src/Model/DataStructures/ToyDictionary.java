package Model.DataStructures;

import Model.Exceptions.DictionaryException;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class ToyDictionary<K, V> implements IADTDictionary<K, V> {
    protected Map<K, V> dictionary;

    public ToyDictionary() {
        dictionary = new ConcurrentHashMap<K, V>();
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
    public Map<K, V> getContent() {
        return dictionary;
    }

    @Override
    public void setContent(Map<K, V> other) {
        dictionary = other;
    }

    @Override
    public IADTDictionary<K, V> deepCopy() {
        IADTDictionary<K, V> new_dict = new ToyDictionary<K, V>();
        for (Map.Entry<K, V> entry : dictionary.entrySet()) {
            try {
                new_dict.put(entry.getKey(), entry.getValue());
            } catch (DictionaryException error) {
                new_dict = null;  // this should normally not happen
            }
        }
        return new_dict;
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
    public String toFileString(int dictionary_type) {
        String type = "";
        switch(dictionary_type) {
            case 1 -> type = "Symbols Table:\n";
            case 2 -> type = "File Table:\n";
            case 3 -> type = "Heap Table:\n";
        }

        if (type.equals(""))
            return type;

        StringBuilder return_string = new StringBuilder(type);
        if (dictionary.isEmpty())
            return return_string.toString() + "\n";

        for (Map.Entry<K, V> entry : dictionary.entrySet()) {
            return_string.append(entry.getKey().toString());
            if (dictionary_type != 2)
                return_string.append(" --> ").append(entry.getValue().toString()).append('\n');
            else
                return_string.append('\n');
        }

        return return_string.toString();
    }
}
