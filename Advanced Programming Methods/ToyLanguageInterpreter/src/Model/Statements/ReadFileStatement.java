package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private IExpression expression;
    private String variable_name;
    private String file_name;

    public ReadFileStatement(IExpression expression, String variable_name) {
        this.expression = expression;
        this.variable_name = variable_name;
        this.file_name = "<file name>";
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        IADTDictionary<String, IValue> symbols_table = state.symbolsTable();
        IADTDictionary<StringValue, BufferedReader> file_table = state.fileTable();

        try {
            if (symbols_table.get(variable_name) == null || !symbols_table.get(variable_name).getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' is undefined or its type is not correct.", variable_name));
            IValue value = expression.eval(symbols_table, state.heapTable());
            if (!value.getType().equals(new StringType()))
                throw new StatementException("Expression should evaluate to a string value.");

            StringValue string_value = (StringValue) value;
            this.file_name = string_value.getValue();
            BufferedReader buffered_reader = file_table.get(string_value);
            if (buffered_reader == null)
                throw new StatementException(String.format("No entry '%s' was found in the file table.", string_value.getValue()));

            String line = buffered_reader.readLine();
            int read_value = 0;

            if (line != null) {
                try {
                    read_value = Integer.parseInt(line);
                } catch (NumberFormatException error) {
                    read_value = 0;
                }
            }
            symbols_table.replace(variable_name, new IntValue(read_value));
        } catch (IOException | DictionaryException | DivisionByZeroException | ExpressionException error) {
            throw new StatementException(error.getMessage());
        }

        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new ReadFileStatement(expression, variable_name);
    }

    @Override
    public String toString() {
        return String.format("readRFile(%s, %s)", file_name, variable_name);
    }
}
