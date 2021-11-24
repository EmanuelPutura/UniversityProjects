import Controller.Controller;
import Model.DataStructures.ADTDictionary;
import Model.DataStructures.ADTHeapDictionary;
import Model.DataStructures.ADTList;
import Model.DataStructures.ADTStack;
import Model.Expressions.*;
import Model.Program.ProgramState;
import Model.Statements.*;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.ReferenceType;
import Model.Types.StringType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;
import View.Refactoring.ExitCommand;
import View.Refactoring.RunExampleCommand;
import View.Refactoring.TextMenu;

import java.io.BufferedReader;
import java.util.Scanner;

public class Main {
    private static String[] readFilePaths(int files_cnt) {
        String[] file_paths = new String[files_cnt];
        Scanner scanner = new Scanner(System.in);

        for (int i = 0; i < files_cnt; ++i) {
            System.out.printf("Enter file path no. %d: ", i + 1);
            file_paths[i] = scanner.nextLine();
        }
        return file_paths;
    }

    private static String[] getFilePaths(int files_cnt) {
        System.out.print("Do you want to read the file paths from the keyboard? [Y|n] - ");
        Scanner scanner = new Scanner(System.in);
        String option = scanner.nextLine();
        while (!option.equals("Y") && !option.equals("n")) {
            System.out.println("Invalid option. Please try again!");
            System.out.print("Do you want to read the file paths from the keyboard? [Y|n] - ");
            option = scanner.nextLine();
        }

        if (option.equals("Y"))
            return readFilePaths(files_cnt);

        String[] file_paths = new String[files_cnt];
        for (int i = 1; i <= files_cnt; ++i)
            file_paths[i - 1] = "src/Files/" + "log" + i + ".txt";
        return file_paths;
    }

    public static void main(String[] args) {
        int files_cnt = 16;
        String[] file_paths = getFilePaths(files_cnt);

        // int v; v = 2; print(v);
        IStatement st1 = new CompoundStatement(new DeclarationStatement("v", new IntType()), new CompoundStatement(
                new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        ProgramState program_state1 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st1);
        Repository repository1 = new Repository(program_state1, file_paths[0]);
        Controller controller1 = new Controller(repository1);

        // int a; int b; a = 2 + 3 * 5; b = a + 1; print(b);
        IStatement st2 = new CompoundStatement(new DeclarationStatement("a", new IntType()), new CompoundStatement(new DeclarationStatement("b", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)),new ArithmeticExpression(
                        new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')), new CompoundStatement(new AssignmentStatement("b",
                        new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));
        ProgramState program_state2 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st2);
        Repository repository2 = new Repository(program_state2, file_paths[1]);
        Controller controller2 = new Controller(repository2);

        // bool a; int v; a = true; (If a Then v = 2 Else v = 3); print(v);
        IStatement st3 = new CompoundStatement(new DeclarationStatement("a", new BoolType()), new CompoundStatement(new DeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompoundStatement(new ConditionalStatement(
                        new VariableExpression("a"),new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(
                        new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
        ProgramState program_state3 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st3);
        Repository repository3 = new Repository(program_state3, file_paths[2]);
        Controller controller3 = new Controller(repository3);

        // int v; v = 2; print(v); int a; a = v + 2; print(a);
        IStatement st4 = new CompoundStatement(st1, new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a",
                new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(2)), '+'))), new PrintStatement(new VariableExpression("a"))));
        ProgramState program_state4 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st4);
        Repository repository4 = new Repository(program_state4, file_paths[3]);
        Controller controller4 = new Controller(repository4);

        // int a; a = 2; int b; b = -5; print(a - b);
        IStatement st5 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(-5))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '+')));
        ProgramState program_state5 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st5);
        Repository repository5 = new Repository(program_state5, file_paths[4]);
        Controller controller5 = new Controller(repository5);

        // int a; a = 2; int b; b = 0; print(a / b);
        IStatement st6 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(0))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '/')));
        ProgramState program_state6 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st6);
        Repository repository6 = new Repository(program_state6, file_paths[5]);
        Controller controller6 = new Controller(repository6);

        // string varf; varf = "test1.txt"; openRFile(varf); int varc; readFile(varf, varc); print(varc); readFile(varf, varc); print(varc); closeRFile(varf);
        IStatement st7 = new CompoundStatement(new DeclarationStatement("varf", new StringType()), new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test1.txt"))),
                new CompoundStatement(new OpenRFileStatement(new VariableExpression("varf")), new CompoundStatement(new DeclarationStatement("varc", new IntType()),
                new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CompoundStatement((
                new ReadFileStatement(new VariableExpression("varf"), "varc")), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CloseRFileStatement(new VariableExpression(("varf")))))))))));
        ProgramState program_state7 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st7);
        Repository repository7 = new Repository(program_state7, file_paths[6]);
        Controller controller7 = new Controller(repository7);

        // int a; int v; a = 25; (If a >= 15 Then v = 2 Else v = 3); print(v);
        IStatement st8 = new CompoundStatement(new DeclarationStatement("a", new IntType()), new CompoundStatement(new DeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(25))), new CompoundStatement(new ConditionalStatement(
                        new RelationalExpression(new VariableExpression("a"), new ValueExpression(new IntValue(15)), ">="),new AssignmentStatement("v",
                        new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));
        ProgramState program_state8 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st8);
        Repository repository8 = new Repository(program_state8, file_paths[7]);
        Controller controller8 = new Controller(repository8);

        // string file1; file1 = "test1.txt"; openRFile(file1); string file2; file2 = "test1.txt"; openRFile(file2);
        IStatement st9 = new CompoundStatement(new DeclarationStatement("file1", new StringType()), new CompoundStatement(new AssignmentStatement("file1", new ValueExpression(new StringValue("test1.txt"))),
                new CompoundStatement(new OpenRFileStatement(new VariableExpression("file1")), new CompoundStatement(new DeclarationStatement("file2", new StringType()), new CompoundStatement(new AssignmentStatement("file2",
                        new ValueExpression(new StringValue("test1.txt"))), new OpenRFileStatement(new VariableExpression("file2")))))));
        ProgramState program_state9 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st9);
        Repository repository9 = new Repository(program_state9, file_paths[8]);
        Controller controller9 = new Controller(repository9);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); print(v); print(a);
        IStatement st10 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));
        ProgramState program_state10 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st10);
        Repository repository10 = new Repository(program_state10, file_paths[9]);
        Controller controller10 = new Controller(repository10);

        //  Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); print(heapRead(v)); print(heapRead(heapRead(a)) + 5);
        IStatement st11 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new PrintStatement(new ArithmeticExpression(
                        new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)), '+')))))));
        ProgramState program_state11 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st11);
        Repository repository11 = new Repository(program_state11, file_paths[10]);
        Controller controller11 = new Controller(repository11);

        // Ref(int) v; new(v, 20); print(heapRead(v)); heapWrite(v, 30); print(heapRead(v) + 5);
        IStatement st12 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                new PrintStatement(new ArithmeticExpression(new HeapReadingExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5)), '+'))))));
        ProgramState program_state12 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st12);
        Repository repository12 = new Repository(program_state12, file_paths[11]);
        Controller controller12 = new Controller(repository12);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st13 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new HeapReadingExpression(
                new HeapReadingExpression(new VariableExpression("a")))))))));
        ProgramState program_state13 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st13);
        Repository repository13 = new Repository(program_state13, file_paths[12]);
        Controller controller13 = new Controller(repository13);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st14 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new HeapReadingExpression(
                                new HeapReadingExpression(new VariableExpression("a")))))))));
        ProgramState program_state14 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st14);
        Repository repository14 = new Repository(program_state14, file_paths[13]);
        Controller controller14 = new Controller(repository14);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st15 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))))))))));
        ProgramState program_state15 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st15);
        Repository repository15 = new Repository(program_state15, file_paths[14]);
        Controller controller15 = new Controller(repository15);

        IStatement st16 = new CompoundStatement(new DeclarationStatement("i", new IntType()), new CompoundStatement(new AssignmentStatement("i", new ValueExpression(new IntValue(5))), new WhileStatement(new RelationalExpression(
                new VariableExpression("i"), new ValueExpression(new IntValue(0)), ">"), new CompoundStatement(new PrintStatement(new VariableExpression("i")),
                new AssignmentStatement("i", new ArithmeticExpression(new VariableExpression("i"), new ValueExpression(new IntValue(1)), '-'))))));
        ProgramState program_state16 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st16);
        Repository repository16 = new Repository(program_state16, file_paths[15]);
        Controller controller16 = new Controller(repository16);


        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExampleCommand("1", st1.toString(), controller1));
        menu.addCommand(new RunExampleCommand("2", st2.toString(), controller2));
        menu.addCommand(new RunExampleCommand("3", st3.toString(), controller3));
        menu.addCommand(new RunExampleCommand("4", st4.toString(), controller4));
        menu.addCommand(new RunExampleCommand("5", st5.toString(), controller5));
        menu.addCommand(new RunExampleCommand("6", st6.toString(), controller6));
        menu.addCommand(new RunExampleCommand("7", st7.toString(), controller7));
        menu.addCommand(new RunExampleCommand("8", st8.toString(), controller8));
        menu.addCommand(new RunExampleCommand("9", st9.toString(), controller9));
        menu.addCommand(new RunExampleCommand("10", st10.toString(), controller10));
        menu.addCommand(new RunExampleCommand("11", st11.toString(), controller11));
        menu.addCommand(new RunExampleCommand("12", st12.toString(), controller12));
        menu.addCommand(new RunExampleCommand("13", st13.toString(), controller13));
        menu.addCommand(new RunExampleCommand("14", st14.toString(), controller14));
        menu.addCommand(new RunExampleCommand("15", st15.toString(), controller15));
        menu.addCommand(new RunExampleCommand("16", st16.toString(), controller16));
        menu.show();
    }
}
