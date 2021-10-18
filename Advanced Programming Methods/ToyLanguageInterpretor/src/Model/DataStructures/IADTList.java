package Model.DataStructures;

import Model.Exceptions.ListException;

public interface IADTList<E> {
    E get(int index) throws ListException;
    void set(int index, E element) throws ListException;
    void add(E element);
    E remove(int index) throws ListException;
    boolean isEmpty();
    int size();
    String toString();
}
