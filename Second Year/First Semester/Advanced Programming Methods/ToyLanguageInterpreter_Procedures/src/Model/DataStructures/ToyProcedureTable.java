package Model.DataStructures;

import Model.Exceptions.DictionaryException;
import Model.Statements.IStatement;
import javafx.util.Pair;

import java.util.List;

public class ToyProcedureTable extends ToyDictionary<String, Pair<List<String>, IStatement>> implements IADTProcedureTable {
}
