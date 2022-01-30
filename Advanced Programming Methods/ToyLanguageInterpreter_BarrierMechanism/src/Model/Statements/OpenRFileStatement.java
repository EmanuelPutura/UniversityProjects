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
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements IStatement {
    private IExpression expression;
    private String file_name;

    public OpenRFileStatement(IExpression expression) {
        this.expression = expression;
        this.file_name = "<file name>";
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue value = expression.eval(state.symbolsTable(), state.heapTable());
            if (value.getType().equals(new StringType())) {
                StringValue string_value = (StringValue) value;
                if (state.fileTable().get(string_value) != null)
                    throw new StatementException(String.format("File name '%s' was already added to the file table.", string_value.toString()));

                String file_name = string_value.getValue();
                this.file_name = file_name;
                BufferedReader buffered_reader = new BufferedReader(new FileReader(file_name));
                state.fileTable().put(string_value, buffered_reader);
            }
            else
                throw new StatementException(String.format("Invalid type error: type '%s' is not valid for a file name.", value.getType().toString()));
        } catch (FileNotFoundException | ExpressionException | DivisionByZeroException | DictionaryException error) {
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
            throw new StatementException(String.format("Expression in statement '%s' is not a string!", toString()));
        } catch (ExpressionException e) {
            throw new StatementException(e.getMessage());
        }
    }

    @Override
    public IStatement deepCopy() {
        return new OpenRFileStatement(expression);
    }

    @Override
    public String toString() {
        return String.format("openRFile(%s)", file_name);
    }
}
