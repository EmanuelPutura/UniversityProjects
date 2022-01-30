package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement {
    private IExpression expression;
    private String file_name;

    public CloseRFileStatement(IExpression expression) {
        this.expression = expression;
        this.file_name = "<file name>";
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue value = expression.eval(state.symbolsTable(), state.heapTable());
            if (!value.getType().equals(new StringType()))
                throw new StatementException("Expression should evaluate to a string.");
            StringValue string_value = (StringValue) value;
            this.file_name = string_value.getValue();
            BufferedReader buffered_reader = state.fileTable().get(string_value);
            if (buffered_reader == null)
                throw new StatementException("Invalid file table data: null value found.");
            buffered_reader.close();
            state.fileTable().remove(string_value);
        } catch (IOException | ExpressionException | DivisionByZeroException | DictionaryException error) {
            throw new StatementException(error.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        try {
            IType type = expression.typeCheck(type_env);
            if (type.equals(new StringType()))
                return type_env;
            throw new StatementException(String.format("Expression from statement '%s' must have string type!", toString()));
        } catch (ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public IStatement deepCopy() {
        return new CloseRFileStatement(expression);
    }

    @Override
    public String toString() {
        return String.format("closeRFile(%s)", file_name);
    }
}
