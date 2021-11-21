package Model.Program;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.DataStructures.IADTList;
import Model.DataStructures.IADTStack;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.ProgramException;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;

public class ProgramState {
    private IADTStack<IStatement> execution_stack;
    private IADTDictionary<String, IValue> symbols_table;
    private IADTList<IValue> out_list;
    private IADTDictionary<StringValue, BufferedReader> file_table;
    private IADTHeapDictionary heap_table;
    private IStatement initial_statement;

    public ProgramState(IADTStack<IStatement> exec_stack, IADTDictionary<String, IValue> sym_table, IADTList<IValue> out_list,
                        IADTDictionary<StringValue, BufferedReader> file_table, IADTHeapDictionary heap_table, IStatement statement) {
        this.execution_stack = exec_stack;
        this.symbols_table = sym_table;
        this.out_list = out_list;
        this.initial_statement = statement.deepCopy();
        this.file_table = file_table;
        this.heap_table = heap_table;
        this.execution_stack.push(statement);
    }

    public IADTStack<IStatement> executionStack() {
        return execution_stack;
    }

    public IADTDictionary<String, IValue> symbolsTable() {
        return symbols_table;
    }

    public IADTList<IValue> outList() {
        return out_list;
    }

    public IADTDictionary<StringValue, BufferedReader> fileTable() {
        return file_table;
    }

    public IADTHeapDictionary heapTable() {
        return heap_table;
    }

    public IStatement getInitialStatement() {
        return initial_statement;
    }

    public void setExecutionStack(IADTStack<IStatement> other) {
        execution_stack = other;
    }

    public void setSymbolsTable(IADTDictionary<String, IValue> other) {
        symbols_table = other;
    }

    public void setOutList(IADTList<IValue> other) {
        out_list = other;
    }

    public void setFileTable(IADTDictionary<StringValue, BufferedReader> other) {
        file_table = other;
    }

    public void setHeapTable(IADTHeapDictionary other) {
        heap_table = other;
    }

    @Override
    public String toString() {
        return String.format("[ProgramState: execution stack (%s), symbols table (%s), out (%s), file table (%s), heap table (%s)]",
                execution_stack.toString(), symbols_table.toString(), out_list.toString(), file_table.toString(), heap_table.toString());
    }

    public String toFileString() throws ProgramException {
        StringBuilder limit = new StringBuilder();
        limit.append("-".repeat(25));
        try {
            return limit.toString() + '\n' + execution_stack.toFileString() + symbols_table.toFileString(1) +
                    out_list.toFileString() + file_table.toFileString(2) + heap_table.toFileString(3) + limit.toString() + '\n';
        } catch (DictionaryException error) {
            throw new ProgramException(error.getMessage());
        }
    }
}