package Model.Utils;

import Model.Statements.CompoundStatement;
import Model.Statements.IStatement;

import java.util.List;

public class MergeStatements {
    public static IStatement merge(List<IStatement> statements) {
        if (statements.size() == 0)
            return null;
        if (statements.size() == 1)
            return statements.get(0);

        return new CompoundStatement(statements.get(0), merge(statements.subList(1, statements.size())));
    }
}
