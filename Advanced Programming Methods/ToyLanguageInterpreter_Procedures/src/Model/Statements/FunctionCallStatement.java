package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.DataStructures.ToyDictionary;
import Model.DataStructures.ToyList;
import Model.Exceptions.*;
import Model.Expressions.IExpression;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;
import javafx.util.Pair;

import java.util.List;
import java.util.Vector;


public class FunctionCallStatement implements IStatement {
    private String function_name;
    private ToyList<IExpression> parameters;

    public FunctionCallStatement(String function_name, List<IExpression> parameters) {
        this.function_name = function_name;
        this.parameters = new ToyList<IExpression>();

        for (int i = 0; i < parameters.size(); ++i)
            this.parameters.add(parameters.get(i));
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            Pair<List<String>, IStatement> function_entry = state.procedureTable().get(function_name);
            if (function_entry == null)
                throw new StatementException(String.format("Function '%s' does not exist!", function_name));

            List<String> param_names = function_entry.getKey();
            IStatement function_body = function_entry.getValue();

            List<IValue> param_values = new Vector<IValue>();
            for (int i = 0; i < parameters.size(); ++i)
                param_values.add(parameters.get(i).eval(state.symbolsTable(), state.heapTable()));

            IADTDictionary<String, IValue> new_symbols_table = new ToyDictionary<String, IValue>();
            int size = param_names.size();
            for (int i = 0; i < size; ++i)
                new_symbols_table.put(param_names.get(i), param_values.get(i));

            state.allSymbolTables().push(new_symbols_table);
            state.executionStack().push(new FunctionReturnStatement());
            state.executionStack().push(function_body);
        } catch (DictionaryException | InvalidIndexException | ListException | ExpressionException | DivisionByZeroException e) {
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException {
        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        List<IExpression> new_params = new Vector<IExpression>();
        for (int i = 0; i < parameters.size(); ++i) {
            try {
                new_params.add(parameters.get(i).deepCopy());
            } catch (ListException | InvalidIndexException e) {
                return null;
            }
        }

        return new FunctionCallStatement(function_name, new_params);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("call_" + function_name + "(");
        for (int i = 0; i < parameters.size() - 1; ++i) {
            try {
                result.append(parameters.get(i).toString()).append(", ");
            } catch (ListException | InvalidIndexException e) {
                return null;
            }
        }

        if (parameters.size() > 0) {
            try {
                result.append(parameters.get(parameters.size() - 1).toString());
                result.append(")");
            } catch (ListException | InvalidIndexException e) {
                return null;
            }
        }

        return result.toString();
    }
}
