package Model.Statements;

import Model.DataStructures.IADTDictionary;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Types.IType;

public interface IStatement {
    ProgramState execute(ProgramState state) throws StatementException, UndeclaredVariableException;
    IADTDictionary<String, IType> typeCheck(IADTDictionary<String, IType> type_env) throws StatementException;
    IStatement deepCopy();

    @Override
    String toString();

    /*
        All statements but for CompoundStatement return the normal result from the toString() method.
        When applied for a CompoundStatements, toPresentationString() returns (toString()), in order to highlight the structure of all compounds statements blocks.
     */
    default String toPresentationString() {
        return toString();
    }
}
