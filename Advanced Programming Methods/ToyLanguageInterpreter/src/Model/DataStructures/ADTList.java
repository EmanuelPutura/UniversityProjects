package Model.DataStructures;

import Model.Exceptions.InvalidIndexException;
import Model.Exceptions.ListException;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

public class ADTList<E> implements IADTList<E> {
    private List<E> list;

    public ADTList() {
        list = new Vector<E>();
    }

    @Override
    public E get(int index) throws ListException, InvalidIndexException {
        if (index < 0 || index >= list.size())
            throw new InvalidIndexException("Index out of bounds!");
        try {
            return list.get(index);
        } catch (Exception exception) {
            throw new ListException(exception.getMessage());
        }
    }

    @Override
    public void set(int index, E element) throws ListException, InvalidIndexException {
        if (index < 0 || index >= list.size())
            throw new InvalidIndexException("Index out of bounds!");
        try {
            list.set(index, element);
        } catch (Exception exception) {
            throw new ListException(exception.getMessage());
        }
    }

    @Override
    public void add(E element) {
        list.add(element);
    }

    @Override
    public E remove(int index) throws ListException, InvalidIndexException {
        if (index < 0 || index >= list.size())
            throw new InvalidIndexException("Index out of bounds!");
        try {
            return list.remove(index);
        } catch (Exception exception) {
            throw new ListException(exception.getMessage());
        }
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public IADTList<E> deepCopy() {
        IADTList<E> new_list = new ADTList<E>();
        for (int i = 0; i < list.size(); ++i)
            new_list.add(list.get(i));
        return new_list;
    }

    @Override
    public List<E> getInnerList() {
        return list;
    }

    @Override
    public String toString() {
        StringBuilder return_string = new StringBuilder("ADTList: [");
        if (list.isEmpty())
            return return_string + "]";

        return_string.append(list.get(0).toString());
        for (int i = 1; i < list.size(); ++i)
            return_string.append(", ").append(list.get(i).toString());

        return_string.append("]");
        return return_string.toString();
    }

    @Override
    public String toFileString() {
        StringBuilder return_string = new StringBuilder("Out List:\n");
        if (list.isEmpty())
            return return_string + "\n";

        for (int i = 0; i < list.size(); ++i)
            return_string.append(list.get(i).toString()).append('\n');
        return return_string.toString();
    }
}
