package Model.DataStructures;

import Model.Exceptions.InvalidIndexException;
import Model.Exceptions.ListException;

public interface IADTList<E> {
    E get(int index) throws ListException, InvalidIndexException;
    void set(int index, E element) throws ListException, InvalidIndexException;
    void add(E element);
    E remove(int index) throws ListException, InvalidIndexException;
    boolean isEmpty();
    int size();

    IADTList<E> deepCopy();

    String toString();
    String toFileString();
}
