package Model.Program;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTList;
import Model.DataStructures.IADTStack;
import Model.Statements.IStatement;
import Model.Values.IValue;

public class ProgramState {
    private IADTStack<IStatement> execution_stack;
    private IADTDictionary<String, IValue> symbols_table;
    private IADTList<IValue> out_list;

    public IADTStack<IStatement> executionStack() {
        return execution_stack;
    }

    public IADTDictionary<String, IValue> symbolsTable() {
        return symbols_table;
    }

    public IADTList<IValue> outList() {
        return out_list;
    }

    public IADTStack<IStatement> getExecutionStack() {
        return execution_stack;
    }

    public IADTDictionary<String, IValue> getSymbolsTable() {
        return symbols_table;
    }

    public IADTList<IValue> getOutList() {
        return out_list;
    }

    ProgramState(IADTStack<IStatement> stack, IADTDictionary<String, IValue> dict, IADTList<IValue> list, IStatement statement) {
        this.execution_stack = stack;
        this.symbols_table = dict;
        this.out_list = list;
        this.execution_stack.push(statement);
    }

    @Override
    public String toString() {
        return String.format("[ProgramState: execution stack (%s), symbols table (%s), out (%s)]", execution_stack.toString(), symbols_table.toString(), out_list.toString());
    }
}