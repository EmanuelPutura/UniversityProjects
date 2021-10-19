import Controller.Controller;
import Model.DataStructures.*;
import Model.Exceptions.EmptyExecutionStackException;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.Program.ProgramState;
import Model.Types.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;
import Repository.IRepository;
import Repository.Repository;
import Testing.ModelTesting.ModelTesting;
import Controller.ControllerException;
import Model.Statements.IStatement;
import Model.Statements.CompoundStatement;
import Model.Statements.DeclarationStatement;
import Model.Statements.AssignmentStatement;
import Model.Statements.PrintStatement;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
        ModelTesting.test();

        IADTStack<IStatement> execution_stack = new ADTStack<IStatement>();
        IADTList<IValue> out_list = new ADTList<IValue>();
        IADTDictionary<String, IValue> symbols_table = new ADTDictionary<String, IValue>();

        // int v; v = 2; print(v);
        IStatement st1 = new CompoundStatement(new DeclarationStatement("v", new IntType()), new CompoundStatement(
                new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));

        ProgramState p1 = new ProgramState(execution_stack, symbols_table, out_list, st1);
        IRepository repository = new Repository(p1);

        Controller controller = new Controller(repository);
        try {
            controller.oneStepExecution(true);
            System.out.println(controller.logs());
            controller.allStepsExecution();
            System.out.println(controller.logs());
        } catch (ControllerException | EmptyExecutionStackException e) {
            e.printStackTrace();
        }
    }
}
