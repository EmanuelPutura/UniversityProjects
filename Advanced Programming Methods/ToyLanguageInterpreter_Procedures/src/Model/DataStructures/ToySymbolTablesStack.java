package Model.DataStructures;

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
}
