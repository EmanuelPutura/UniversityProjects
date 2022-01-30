package Model.DataStructures;

import Model.Exceptions.EmptyStackException;
import Model.Statements.IStatement;

import java.util.Stack;

public class ToyStack<E> implements IADTStack<E> {
    protected Stack<E> stack;

    public ToyStack() {
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
    public IADTStack<E> deepCopy() {
        IADTStack<E> new_stack = new ToyStack<E>();
        Stack<E> temp_stack = new Stack<E>();

        while (!stack.empty())
            temp_stack.push(stack.pop());

        while (!temp_stack.empty()) {
            stack.push(temp_stack.peek());
            new_stack.push(temp_stack.pop());
        }

        return new_stack;
    }

    @Override
    public Stack<E> getContent() {
        return stack;
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

    @Override
    public String toFileString() {
        StringBuilder return_string = new StringBuilder("Execution Stack:\n");
        if (stack.isEmpty())
            return return_string.toString() + '\n';

        Stack<E> stack_copy = new Stack<E>();
        while (!stack.isEmpty()) {
            if (stack.peek() instanceof IStatement)
                return_string.append(((IStatement) stack.peek()).toPresentationString()).append('\n');
            else
                return_string.append(stack.peek().toString()).append('\n');
            stack_copy.push(stack.pop());
        }

        while (!stack_copy.isEmpty()) {
            stack.push(stack_copy.pop());
        }

        return return_string.toString();
    }
}
