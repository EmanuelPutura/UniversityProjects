package View.FirstImplementation;

import Model.DataStructures.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.Program.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.IRepository;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;

public class DefaultTestPrograms {
    public static void addAll(IRepository repository) {
        // int v; v = 2; print(v);
        IStatement st1 = new CompoundStatement(new DeclarationStatement("v", new IntType()), new CompoundStatement(
                new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));

        // int a; int b; a = 2 + 3 * 5; b = a + 1; print(b);
        IStatement st2 = new CompoundStatement(new DeclarationStatement("a", new IntType()), new CompoundStatement(new DeclarationStatement("b", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)),new ArithmeticExpression(
                new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')), new CompoundStatement(new AssignmentStatement("b",
                new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));

        // bool a; int v; a = true; (If a Then v = 2 Else v = 3); print(v);
        IStatement st3 = new CompoundStatement(new DeclarationStatement("a", new BoolType()), new CompoundStatement(new DeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompoundStatement(new ConditionalStatement(
                new VariableExpression("a"),new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(
                new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));

        // int v; v = 2; print(v); int a; a = v + 2; print(a);
        IStatement st4 = new CompoundStatement(st1, new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a",
                new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(2)), '+'))), new PrintStatement(new VariableExpression("a"))));

        // int a; a = 2; int b; b = -5; print(a - b);
        IStatement st5 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(-5))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '+')));

        // int a; a = 2; int b; b = 0; print(a / b);
        IStatement st6 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(0))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '/')));

        List<ProgramState> states = new ArrayList<ProgramState>();
        ProgramState program_state1 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st1);
        ProgramState program_state2 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st2);
        ProgramState program_state3 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st3);
        ProgramState program_state4 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st4);
        ProgramState program_state5 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st5);
        ProgramState program_state6 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(), new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st6);

        states.add(program_state1);
        states.add(program_state2);
        states.add(program_state3);
        states.add(program_state4);
        states.add(program_state5);
        states.add(program_state6);
        repository.setProgramStateList(states);
    }
}
