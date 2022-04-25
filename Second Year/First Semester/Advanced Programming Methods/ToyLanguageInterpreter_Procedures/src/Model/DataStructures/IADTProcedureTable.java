package Model.DataStructures;

import Model.Statements.IStatement;
import javafx.util.Pair;

import java.util.List;

public interface IADTProcedureTable extends IADTDictionary<String, Pair<List<String>, IStatement>> {
}
