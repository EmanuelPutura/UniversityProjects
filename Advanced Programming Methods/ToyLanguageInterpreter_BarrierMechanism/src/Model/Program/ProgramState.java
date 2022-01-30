package Model.Program;

import Model.DataStructures.*;
import Model.Exceptions.*;
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
    private IADTLockTable lock_table;
    private IADTBarrierTable barrier_table;
    private IStatement initial_statement;

    private int id;
    private static int current_generated_id = 0;

    public ProgramState(IADTStack<IStatement> exec_stack, IADTDictionary<String, IValue> sym_table, IADTList<IValue> out_list,
                        IADTDictionary<StringValue, BufferedReader> file_table, IADTHeapDictionary heap_table, IADTLockTable lock_table,
                        IADTBarrierTable barrier_table, IStatement statement) {
        this.execution_stack = exec_stack;
        this.symbols_table = sym_table;
        this.out_list = out_list;
        this.initial_statement = statement.deepCopy();
        this.file_table = file_table;
        this.heap_table = heap_table;
        this.lock_table = lock_table;
        this.barrier_table = barrier_table;
        this.execution_stack.push(statement);
        this.id = getID();
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

    public IADTLockTable lockTable() {
        return lock_table;
    }

    public IADTBarrierTable barrierTable() {
        return barrier_table;
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

    public void setLockTable(IADTLockTable other) {
        lock_table = other;
    }

    public void setBarrierTable(IADTBarrierTable other) {
        barrier_table = other;
    }

    public int programID() {
        return id;
    }

    public Boolean isNotCompleted() {
        return !execution_stack.empty();
    }

    public ProgramState oneStepExecution() throws ProgramException, EmptyExecutionStackException {
        if (execution_stack.empty())
            throw new EmptyExecutionStackException("Empty execution stack error!");
        IStatement current_statement = null;
        try {
            current_statement = execution_stack.pop();
            return current_statement.execute(this);
        } catch (StackException | StatementException | UndeclaredVariableException error) {
            throw new ProgramException(error.getMessage());
        }
    }

    private static synchronized int getID() {
        return ++current_generated_id;
    }

    @Override
    public String toString() {
        return logProgramStateExecution();
    }

    public String logProgramStateExecution() {
        StringBuilder limit = new StringBuilder();
        limit.append("-".repeat(25));
        return limit.toString() + String.format("\nProgram ID: %d", id) + '\n' + execution_stack.toFileString() + symbols_table.toFileString(1) +
                out_list.toFileString() + file_table.toFileString(2) + heap_table.toFileString(3) + limit.toString() + '\n';
    }
}