package Model.DataStructures;

import Model.Statements.IStatement;
import Model.Values.IValue;

import java.util.Stack;

public class ToySymbolTablesStack extends ToyStack<IADTDictionary<String, IValue>> {
    @Override
    public ToySymbolTablesStack deepCopy() {
        ToySymbolTablesStack new_stack = new ToySymbolTablesStack();
        Stack<IADTDictionary<String, IValue>> temp_stack = new Stack<IADTDictionary<String, IValue>>();

        while (!this.stack.empty())
            temp_stack.push(this.stack.pop());

        while (!temp_stack.empty()) {
            stack.push(temp_stack.peek());
            new_stack.push(temp_stack.pop().deepCopy());
        }

        return new_stack;
    }

    @Override
    public String toFileString() {
        StringBuilder return_string = new StringBuilder("Symbol Tables Stack:\n");
        if (stack.isEmpty())
            return return_string.toString() + '\n';

        Stack<IADTDictionary<String, IValue>> stack_copy = new Stack<IADTDictionary<String, IValue>>();
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
