package Model.Statements;

import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement {
    private IExpression expression;

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue value = expression.eval(state.symbolsTable());
            if (!value.getType().equals(new StringType()))
                throw new StatementException("Expression should evaluate to a string.");
            StringValue string_value = (StringValue) value;
            BufferedReader buffered_reader = state.fileTable().get(string_value);
            if (buffered_reader == null)
                throw new StatementException("Invalid file table data: null value found.");
            buffered_reader.close();
            state.fileTable().remove(string_value);
        } catch (IOException | ExpressionException | DivisionByZeroException | DictionaryException error) {
            throw new StatementException(error.getMessage());
        }

        return state;
    }
}
