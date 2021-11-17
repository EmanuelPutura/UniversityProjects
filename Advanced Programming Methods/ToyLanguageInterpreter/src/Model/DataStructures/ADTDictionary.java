package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Values.StringValue;

import java.util.Dictionary;
import java.util.Enumeration;
import java.util.Hashtable;

public class ADTDictionary<K, V> implements IADTDictionary<K, V> {
    private Hashtable<K, V> dictionary;

    public ADTDictionary() {
        dictionary = new Hashtable<K, V>();
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
    public V search(K key) throws DictionaryException {
        try {
            if (!dictionary.containsKey(key))
                return null;
            return dictionary.get(key);
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

        Enumeration<K> current = dictionary.keys();
        K key = current.nextElement();
        return_string.append(key).append(": ").append(dictionary.get(key));


        while (current.hasMoreElements()) {
            key = current.nextElement();
            return_string.append(", ").append(key).append(": ").append(dictionary.get(key));
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

        Enumeration<K> current = dictionary.keys();
        K key = null;

        while (current.hasMoreElements()) {
            key = current.nextElement();
            return_string.append(key);
            if (print_values)
                return_string.append(" --> ").append(dictionary.get(key)).append('\n');
            else return_string.append('\n');
        }

        return return_string.toString();
    }
}
