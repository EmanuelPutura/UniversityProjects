package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.ReferenceType;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

import javax.swing.plaf.nimbus.State;

public class HeapWritingStatement implements IStatement {
    private String variable_name;
    private IExpression expression;

    public HeapWritingStatement(String variable_name, IExpression expression) {
        this.variable_name = variable_name;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTDictionary<String, IValue> symbols_table = state.symbolsTable();
        IADTHeapDictionary heap_table = state.heapTable();

        IValue variable_value = null;
        try {
            variable_value = symbols_table.get(variable_name);
            if (variable_value == null)
                throw new UndeclaredVariableException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!(variable_value instanceof ReferenceValue))
                throw new StatementException(String.format("Variable '%s' should be of reference type!", variable_name));

            ReferenceValue variable_ref_value = (ReferenceValue) variable_value;
            int heap_address = variable_ref_value.getHeapAddress();
            if (heap_table.get(heap_address) == null)
                throw new StatementException(String.format("Heap address '%d' is not valid!", heap_address));

            IValue expression_value = expression.eval(symbols_table, heap_table);
            if (!expression_value.getType().equals(((ReferenceType) variable_ref_value.getType()).getLocationType()))
                throw new StatementException(String.format("Location pointed by heap address '%d' does not match the type of variable '%s'!", heap_address, variable_name));

            heap_table.replace(heap_address, expression_value);
        } catch (DictionaryException | ExpressionException | DivisionByZeroException error) {
            throw new StatementException(error.getMessage());
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapWritingStatement(variable_name, expression);
    }

    @Override
    public String toString() {
        return String.format("heapWrite(%s, %s)", variable_name, expression.toString());
    }
}
