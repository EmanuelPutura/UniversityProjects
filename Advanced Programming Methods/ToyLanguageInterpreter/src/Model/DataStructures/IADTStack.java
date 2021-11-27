package Model.DataStructures;

import Model.Exceptions.StackException;

public interface IADTStack<E> {
    E pop() throws StackException;
    E top() throws StackException;
    void push(E element);
    boolean empty();

    IADTStack<E> deepCopy();

    String toString();
    String toFileString();
}
