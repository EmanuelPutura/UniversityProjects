import Controller.Controller;
import Model.DataStructures.ADTDictionary;
import Model.DataStructures.ADTHeapDictionary;
import Model.DataStructures.ADTList;
import Model.DataStructures.ADTStack;
import Model.Exceptions.StatementException;
import Model.Expressions.*;
import Model.Program.ProgramState;
import Model.Statements.*;
import Model.Types.*;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.Repository;
import View.Console.ExitCommand;
import View.Console.RunExampleCommand;
import View.Console.TextMenu;
import View.GUI.ControllerSelectWindow;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main extends Application {
    private static List<Controller> controllers = new ArrayList<Controller>();

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

        // System.out.println("Working Directory = " + System.getProperty("user.dir"));
        String[] file_paths = new String[files_cnt];
        for (int i = 1; i <= files_cnt; ++i)
            file_paths[i - 1] = "src/Files/" + "log" + i + ".txt";
        return file_paths;
    }

    private static void typeCheck(IStatement statement) {
        try {
            statement.typeCheck(new ADTDictionary<String, IType>());
        } catch (StatementException e) {
            System.out.println(e.getMessage() + '\n');
        }
    }

    private static void initPrograms() {
        int files_cnt = 18;
        String[] file_paths = getFilePaths(files_cnt);

        // int v; v = 2; print(v);
        IStatement st1 = new CompoundStatement(new DeclarationStatement("v", new IntType()), new CompoundStatement(
                new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));

        ProgramState program_state1 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st1);
        Repository repository1 = new Repository(program_state1, file_paths[0]);
        Controller controller1 = new Controller(repository1);
        controllers.add(controller1);

        // int a; int b; a = 2 + 3 * 5; b = a + 1; print(b);
        IStatement st2 = new CompoundStatement(new DeclarationStatement("a", new IntType()), new CompoundStatement(new DeclarationStatement("b", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression(new ValueExpression(new IntValue(2)),new ArithmeticExpression(
                        new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5)), '*'), '+')), new CompoundStatement(new AssignmentStatement("b",
                        new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), '+')), new PrintStatement(new VariableExpression("b"))))));

        ProgramState program_state2 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st2);
        Repository repository2 = new Repository(program_state2, file_paths[1]);
        Controller controller2 = new Controller(repository2);
        controllers.add(controller2);

        // bool a; int v; a = true; (If a Then v = 2 Else v = 3); print(v);
        IStatement st3 = new CompoundStatement(new DeclarationStatement("a", new BoolType()), new CompoundStatement(new DeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new BoolValue(true))), new CompoundStatement(new ConditionalStatement(
                        new VariableExpression("a"),new AssignmentStatement("v", new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(
                        new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));

        ProgramState program_state3 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st3);
        Repository repository3 = new Repository(program_state3, file_paths[2]);
        Controller controller3 = new Controller(repository3);
        controllers.add(controller3);

        // int v; v = 2; print(v); int a; a = v + 2; print(a);
        IStatement st4 = new CompoundStatement(st1, new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a",
                new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(2)), '+'))), new PrintStatement(new VariableExpression("a"))));

        ProgramState program_state4 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st4);
        Repository repository4 = new Repository(program_state4, file_paths[3]);
        Controller controller4 = new Controller(repository4);
        controllers.add(controller4);

        // int a; a = 2; int b; b = -5; print(a - b);
        IStatement st5 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(-5))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '+')));

        ProgramState program_state5 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st5);
        Repository repository5 = new Repository(program_state5, file_paths[4]);
        Controller controller5 = new Controller(repository5);
        controllers.add(controller5);

        // int a; a = 2; int b; b = 0; print(a / b);
        IStatement st6 = new CompoundStatement(new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a", new ValueExpression(
                new IntValue(2)))), new CompoundStatement(new DeclarationStatement("b", new IntType()), new AssignmentStatement("b", new ValueExpression(new IntValue(0))))), new PrintStatement(
                new ArithmeticExpression(new VariableExpression("a"), new VariableExpression("b"), '/')));

        ProgramState program_state6 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st6);
        Repository repository6 = new Repository(program_state6, file_paths[5]);
        Controller controller6 = new Controller(repository6);
        controllers.add(controller6);

        // string varf; varf = "test1.txt"; openRFile(varf); int varc; readFile(varf, varc); print(varc); readFile(varf, varc); print(varc); closeRFile(varf);
        IStatement st7 = new CompoundStatement(new DeclarationStatement("varf", new StringType()), new CompoundStatement(new AssignmentStatement("varf", new ValueExpression(new StringValue("test1.txt"))),
                new CompoundStatement(new OpenRFileStatement(new VariableExpression("varf")), new CompoundStatement(new DeclarationStatement("varc", new IntType()),
                        new CompoundStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CompoundStatement((
                                new ReadFileStatement(new VariableExpression("varf"), "varc")), new CompoundStatement(new PrintStatement(new VariableExpression("varc")), new CloseRFileStatement(new VariableExpression(("varf")))))))))));

        ProgramState program_state7 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st7);
        Repository repository7 = new Repository(program_state7, file_paths[6]);
        Controller controller7 = new Controller(repository7);
        controllers.add(controller7);

        // int a; int v; a = 25; (If a >= 15 Then v = 2 Else v = 3); print(v);
        IStatement st8 = new CompoundStatement(new DeclarationStatement("a", new IntType()), new CompoundStatement(new DeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignmentStatement("a", new ValueExpression(new IntValue(25))), new CompoundStatement(new ConditionalStatement(
                        new RelationalExpression(new VariableExpression("a"), new ValueExpression(new IntValue(15)), ">="),new AssignmentStatement("v",
                        new ValueExpression(new IntValue(2))), new AssignmentStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v"))))));

        ProgramState program_state8 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st8);
        Repository repository8 = new Repository(program_state8, file_paths[7]);
        Controller controller8 = new Controller(repository8);
        controllers.add(controller8);

        // string file1; file1 = "test1.txt"; openRFile(file1); string file2; file2 = "test1.txt"; openRFile(file2);
        IStatement st9 = new CompoundStatement(new DeclarationStatement("file1", new StringType()), new CompoundStatement(new AssignmentStatement("file1", new ValueExpression(new StringValue("test1.txt"))),
                new CompoundStatement(new OpenRFileStatement(new VariableExpression("file1")), new CompoundStatement(new DeclarationStatement("file2", new StringType()), new CompoundStatement(new AssignmentStatement("file2",
                        new ValueExpression(new StringValue("test1.txt"))), new OpenRFileStatement(new VariableExpression("file2")))))));

        ProgramState program_state9 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st9);
        Repository repository9 = new Repository(program_state9, file_paths[8]);
        Controller controller9 = new Controller(repository9);
        controllers.add(controller9);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); print(v); print(a);
        IStatement st10 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));

        ProgramState program_state10 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st10);
        Repository repository10 = new Repository(program_state10, file_paths[9]);
        Controller controller10 = new Controller(repository10);
        controllers.add(controller10);

        //  Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); print(heapRead(v)); print(heapRead(heapRead(a)) + 5);
        IStatement st11 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new PrintStatement(new ArithmeticExpression(
                                new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)), '+')))))));

        ProgramState program_state11 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st11);
        Repository repository11 = new Repository(program_state11, file_paths[10]);
        Controller controller11 = new Controller(repository11);
        controllers.add(controller11);

        // Ref(int) v; new(v, 20); print(heapRead(v)); heapWrite(v, 30); print(heapRead(v) + 5);
        IStatement st12 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new CompoundStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                        new PrintStatement(new ArithmeticExpression(new HeapReadingExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5)), '+'))))));

        ProgramState program_state12 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st12);
        Repository repository12 = new Repository(program_state12, file_paths[11]);
        Controller controller12 = new Controller(repository12);
        controllers.add(controller12);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st13 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new HeapReadingExpression(
                                new HeapReadingExpression(new VariableExpression("a")))))))));

        ProgramState program_state13 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st13);
        Repository repository13 = new Repository(program_state13, file_paths[12]);
        Controller controller13 = new Controller(repository13);
        controllers.add(controller13);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st14 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new HeapReadingExpression(
                                new HeapReadingExpression(new VariableExpression("a")))))))));

        ProgramState program_state14 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st14);
        Repository repository14 = new Repository(program_state14, file_paths[13]);
        Controller controller14 = new Controller(repository14);
        controllers.add(controller14);

        // Ref(int) v; new(v, 20); Ref(Ref(int)) a; new(a, v); new(v, 30); print(heapRead(heapRead(a)));
        IStatement st15 = new CompoundStatement(new DeclarationStatement("v", new ReferenceType(new IntType())), new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))), new CompoundStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                                new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))))))))));

        ProgramState program_state15 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st15);
        Repository repository15 = new Repository(program_state15, file_paths[14]);
        Controller controller15 = new Controller(repository15);
        controllers.add(controller15);

        IStatement st16 = new CompoundStatement(new DeclarationStatement("i", new IntType()), new CompoundStatement(new AssignmentStatement("i", new ValueExpression(new IntValue(5))), new WhileStatement(new RelationalExpression(
                new VariableExpression("i"), new ValueExpression(new IntValue(0)), ">"), new CompoundStatement(new PrintStatement(new VariableExpression("i")),
                new AssignmentStatement("i", new ArithmeticExpression(new VariableExpression("i"), new ValueExpression(new IntValue(1)), '-'))))));

        ProgramState program_state16 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st16);
        Repository repository16 = new Repository(program_state16, file_paths[15]);
        Controller controller16 = new Controller(repository16);
        controllers.add(controller16);

        /*
            int v; Ref(int) a; v = 10; new(a, 22);
            fork(heapWrite(a, 30); v = 32; print(v); print(heapRead(a)));
            print(v); print(heapRead(a));
         */
        IStatement st17 = new CompoundStatement(new DeclarationStatement("v", new IntType()), new CompoundStatement(new DeclarationStatement("a", new ReferenceType(new IntType())), new CompoundStatement(
                new AssignmentStatement("v", new ValueExpression(new IntValue(10))), new CompoundStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))), new CompoundStatement(
                new ForkStatement(new CompoundStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))), new CompoundStatement(new AssignmentStatement("v", new ValueExpression(new IntValue(32))), new CompoundStatement(
                        new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))
                )))), new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));

        ProgramState program_state17 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st17);
        Repository repository17 = new Repository(program_state17, file_paths[16]);
        Controller controller17 = new Controller(repository17);
        controllers.add(controller17);

        // int v; v = 2; print(v); int a; a = v + "hey"; print(a);
        IStatement st18 = new CompoundStatement(st1, new CompoundStatement(new CompoundStatement(new DeclarationStatement("a", new IntType()), new AssignmentStatement("a",
                new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new StringValue("hey")), '+'))), new PrintStatement(new VariableExpression("a"))));

        ProgramState program_state18 = new ProgramState(new ADTStack<IStatement>(), new ADTDictionary<String, IValue>(), new ADTList<IValue>(),
                new ADTDictionary<StringValue, BufferedReader>(), new ADTHeapDictionary(), st18);
        Repository repository18 = new Repository(program_state18, file_paths[17]);
        Controller controller18 = new Controller(repository18);
        controllers.add(controller18);
    }

    private static void consoleLaunch(String[] args) {
        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "exit"));
        for (var i = 1; i <= controllers.size(); ++i) {
            String key = Integer.toString(i);
            IStatement statement = controllers.get(i - 1).getRepository().getInitialProgramState().getInitialStatement();
            menu.addCommand(new RunExampleCommand(key, statement.toPresentationString(), controllers.get(i - 1)));
            typeCheck(statement);
        }

        menu.show();
    }

    private static void guiLaunch(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(new File("src/View/GUI/SelectWindow.fxml").toURI().toURL());
        StackPane root = (StackPane) loader.load();
        ControllerSelectWindow select_window_controller = loader.getController();
        select_window_controller.setPrograms(controllers);

        Scene scene = new Scene(root,400,150);
        scene.getStylesheets().add(new File("src/View/GUI/SelectWindow.css").toURI().toURL().toExternalForm());
        stage.setScene(scene);
        stage.setWidth(1000);
        stage.setHeight(600);
        stage.setTitle("Select a program");
        stage.show();
    }

    public static void main(String[] args) {
        initPrograms();
//        consoleLaunch(args);
        guiLaunch(args);
    }
}
