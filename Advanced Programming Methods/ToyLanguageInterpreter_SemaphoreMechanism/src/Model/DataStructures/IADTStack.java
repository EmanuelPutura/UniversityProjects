package Model.DataStructures;

import Model.Exceptions.StackException;

import java.util.Stack;

public interface IADTStack<E> {
    E pop() throws StackException;
    E top() throws StackException;
    void push(E element);
    boolean empty();

    IADTStack<E> deepCopy();
    Stack<E> getContent();

    String toString();
    String toFileString();
}
