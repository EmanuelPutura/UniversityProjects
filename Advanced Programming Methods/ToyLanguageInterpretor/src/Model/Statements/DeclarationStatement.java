package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.StatementException;
import Model.Program.ProgramState;
import Model.Types.IType;
import Model.Values.IValue;

public class DeclarationStatement implements IStatement {
    private String label;
    private IType type;

    public DeclarationStatement(String label, IType type) {
        this.label = label;
        this.type = type;
    }

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        IADTDictionary<String, IValue> symbols_table = state.symbolsTable();

        try {
            if (symbols_table.search(label) == null)
                symbols_table.put(label, type.defaultValue());
            else
                throw new StatementException(String.format("Variable '%s' was already declared!", label));
        } catch (DictionaryException exception) {
            throw new StatementException(exception.getMessage());
        }

        return state;
    }
}
