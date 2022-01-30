package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class AssignmentStatement implements IStatement {
    private String label;
    private IExpression expression;

    public AssignmentStatement(String label, IExpression expression) {
        this.label = label;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTDictionary<String, IValue> symbols_table = state.symbolsTable();
        try {
            if (symbols_table.get(label) != null) {
                IValue value = expression.eval(symbols_table, state.heapTable());
                IType type = symbols_table.get(label).getType();

                if (value.getType().equals(type))
                    symbols_table.replace(label, value);
                else
                    throw new StatementException(String.format("The declared type of variable '%s' and the type of the assigned expression do not match!", label));
            }
            else
                throw new UndeclaredVariableException(String.format("Variable '%s' was not declared!", label));
        } catch (DictionaryException | ExpressionException | UndeclaredVariableException | DivisionByZeroException exception) {
            throw new StatementException(exception.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            IType var_type = type_env.get(label);
            IType exp_type = expression.typeCheck(type_env);
            if (var_type.equals(exp_type))
                return type_env;
            throw new StatementException(String.format("Assignment error: left and right hand-side of expression '%s' have different types!", toString()));
        } catch (DictionaryException | ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public IStatement deepCopy() {
        return new AssignmentStatement(label, expression);
    }

    @Override
    public String toString() {
        return label + " = " + expression.toString();
    }
}
