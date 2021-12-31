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
}
