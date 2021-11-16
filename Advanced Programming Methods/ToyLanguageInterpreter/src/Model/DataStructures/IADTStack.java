package Model.DataStructures;

import Model.Exceptions.StackException;

public interface IADTStack<E> {
    E pop() throws StackException;
    E top() throws StackException;
    void push(E element);
    boolean empty();
    String toString();
    String toFileString();
}
