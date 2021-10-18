package Model.DataStructures;

import Model.Exceptions.StackException;

import java.util.Stack;

public class ADTStack<E> implements IADTStack<E> {
    private Stack<E> stack;

    public ADTStack() {
        stack = new Stack<E>();
    }

    @Override
    public E pop() throws StackException {
        try {
            return stack.pop();
        } catch (java.util.EmptyStackException exception) {
            throw new StackException("Cannot pop from an empty stack!");
        }
    }

    @Override
    public E top() throws StackException {
        try {
            return stack.peek();
        } catch (java.util.EmptyStackException exception) {
            throw new StackException("Cannot extract the top from an empty stack!");
        }
    }

    @Override
    public void push(E element) {
        stack.push(element);
    }

    @Override
    public boolean empty() {
        return stack.empty();
    }

    @Override
    public String toString() {
        try {
            return "Stack, top element is " + top();
        } catch (StackException e) {
            return "Empty stack";
        }
    }
}
