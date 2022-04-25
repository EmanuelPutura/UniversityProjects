package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import javafx.util.Pair;

import java.util.Vector;

public class NewSemaphoreStatement implements IStatement {
    private String variable_name;
    private IExpression n_expression;

    public NewSemaphoreStatement(String variable_name, IExpression n_expression) {
        this.variable_name = variable_name;
        this.n_expression = n_expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue expression_value = n_expression.eval(state.symbolsTable(), state.heapTable());
            if (!expression_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Expression '%s' should evaluate to an integer!", n_expression.toString()));

            int expression_int = ((IntValue) expression_value).getValue();
            int new_location = state.semaphoreTable().put(new Pair<>(expression_int, new Vector<>()));

            IValue variable_value = state.symbolsTable().get(variable_name);
            if (variable_value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!variable_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should have integer type!", variable_name));

            state.symbolsTable().replace(variable_name, new IntValue(new_location));
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
                throw new StatementException(String.format("Variable '%s' should have integer type!", variable_name));
            if (!n_expression.typeCheck(type_env).equals(new IntType()))
                throw new StatementException(String.format("Expression '%s' should evaluate to an integer!", n_expression.toString()));
        } catch (DictionaryException | ExpressionException e) {
            throw new StatementException(e.getMessage());
        }

        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new NewSemaphoreStatement(variable_name, n_expression);
    }

    @Override
    public String toString() {
        return String.format("newSemaphore(%s, %s)", variable_name, n_expression.toString());
    }
}
