package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.IADTHeapDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.ReferenceType;
import Model.Values.IValue;
import Model.Values.ReferenceValue;

import java.lang.ref.Reference;

public class HeapAllocationStatement implements IStatement {
    private String variable_name;
    private IExpression expression;

    public HeapAllocationStatement(String variable_name, IExpression expression) {
        this.variable_name = variable_name;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTDictionary<String, IValue> symbols_table = state.symbolsTable();
        IADTHeapDictionary heap_table = state.heapTable();

        try {
            IValue dict_value = symbols_table.get(variable_name);
            if (dict_value == null)
                throw new UndeclaredVariableException(String.format("Variable '%s' was not declared!", variable_name));
            if (!(dict_value instanceof ReferenceValue))
                throw new StatementException(String.format("Variable '%s' must be of reference type!", variable_name));

            IValue expression_value = expression.eval(symbols_table, state.heapTable());
            IType location_type = ((ReferenceType) dict_value.getType()).getLocationType();

            if (!expression_value.getType().equals(location_type))
                throw new StatementException("Reference location type does not match with expression type!");

            int heap_address = heap_table.put(expression_value);
            ReferenceValue reference_value = (ReferenceValue) dict_value;
//            reference_value.setHeapAddress(heap_address);
            ReferenceValue new_reference = new ReferenceValue(heap_address, ((ReferenceType) reference_value.getType()).getLocationType());
            symbols_table.replace(variable_name, new_reference);
        } catch (DictionaryException | DivisionByZeroException | ExpressionException error) {
            throw new StatementException(error.getMessage());
        }

        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new HeapAllocationStatement(variable_name, expression);
    }

    @Override
    public String toString() {
        return String.format("new(%s, %s)", variable_name, expression.toString());
    }
}
