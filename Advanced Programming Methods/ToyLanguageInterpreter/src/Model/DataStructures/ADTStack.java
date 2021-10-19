package Model.DataStructures;

import Model.Exceptions.EmptyStackException;
import Model.Exceptions.StackException;

import java.util.Stack;

public class ADTStack<E> implements IADTStack<E> {
    private Stack<E> stack;

    public ADTStack() {
        stack = new Stack<E>();
    }

    @Override
    public E pop() throws EmptyStackException {
        try {
            return stack.pop();
        } catch (java.util.EmptyStackException exception) {
            throw new EmptyStackException("Cannot pop from an empty stack!");
        }
    }

    @Override
    public E top() throws EmptyStackException {
        try {
            return stack.peek();
        } catch (java.util.EmptyStackException exception) {
            throw new EmptyStackException("Cannot extract the top from an empty stack!");
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
        StringBuilder return_string = new StringBuilder("Stack: (");
        if (stack.isEmpty())
            return return_string.toString() + ')';

        Stack<E> stack_copy = new Stack<E>();
        while (!stack.isEmpty()) {
            stack_copy.push(stack.pop());
        }

        stack.push(stack_copy.pop());
        return_string.append(stack.peek().toString());

        while (!stack_copy.isEmpty()) {
            stack.push(stack_copy.pop());
            return_string.append(", ").append(stack.peek().toString());
        }

        return return_string.toString();
    }
}
