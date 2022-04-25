package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.ExpressionException;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import javafx.util.Pair;

import java.util.List;

public class BarrierAwaitStatement implements IStatement {
    private String variable_name;

    public BarrierAwaitStatement(String variable_name) {
        this.variable_name = variable_name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException {
        try {
            IValue var_value = state.symbolsTable().get(variable_name);
            if (var_value == null)
                throw new StatementException(String.format("Variable '%s' has not been declared!", variable_name));
            if (!var_value.getType().equals(new IntType()))
                throw new StatementException(String.format("Variable '%s' should be of integer type!", variable_name));

            int var_int = ((IntValue) var_value).getValue();
            Pair<Integer, List<Integer>> barrier_table_entry = state.barrierTable().get(var_int);
            if (barrier_table_entry == null)
                throw new StatementException("Invalid barrier table location!");

            int barrier_value = barrier_table_entry.getKey();
            List<Integer> barrier_programs = barrier_table_entry.getValue();

            if (barrier_value > barrier_programs.size()) {
                if (!barrier_programs.contains(state.programID()))
                    barrier_programs.add(state.programID());
                state.executionStack().push(this);
            }
        } catch (DictionaryException e) {
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
        } catch (DictionaryException e) {
            throw new StatementException(e.getMessage());
        }

        return type_env;
    }

    @Override
    public IStatement deepCopy() {
        return new BarrierAwaitStatement(variable_name);
    }

    @Override
    public String toString() {
        return String.format("barrierAwait(%s)", variable_name);
    }
}
