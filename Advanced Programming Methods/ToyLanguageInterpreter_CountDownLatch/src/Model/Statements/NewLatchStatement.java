package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

import javax.swing.plaf.nimbus.State;

public class NewLatchStatement implements IStatement {
    private String variable_name;
    private IExpression expression_n;

    public NewLatchStatement(String variable_name, IExpression expression_n) {
        this.variable_name = variable_name;
        this.expression_n = expression_n;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue expression_val = expression_n.eval(state.symbolsTable(), state.heapTable());
            if (!expression_val.getType().equals(new IntType()))
                throw new StatementException(String.format("Expression '%s' should evaluate to an integer!", expression_n.toString()));

            int latch_n = ((IntValue) expression_val).getValue();
            int latch_location = state.latchTable().put(latch_n);

            IValue var_value = state.symbolsTable().get(variable_name);
            if (var_value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!var_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should be of integer type!", variable_name));
            state.symbolsTable().replace(variable_name, new IntValue(latch_location));
        } catch (ExpressionException | DivisionByZeroException | DictionaryException e) {
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            IType var_type = type_env.get(variable_name);
            if (var_type == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!var_type.equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should be of integer type!", variable_name));

            IType expression_type = expression_n.typeCheck(type_env);
            if (!expression_type.equals(new IntType()))
                throw new StatementException(String.format("Expression '%s' should evaluate to an integer!", expression_n.toString()));
        } catch (DictionaryException | ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
        
        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new NewLatchStatement(variable_name, expression_n);
    }

    @Override
    public String toString() {
        return String.format("newLatch(%s, %s)", variable_name, expression_n.toString());
    }
}
