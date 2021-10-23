import Controller.Controller;
import Repository.IRepository;
import Repository.Repository;
import Testing.ModelTesting.ModelTesting;
import View.ConsoleUI;
import View.IUserInterface;

public class Main {
    public static void main(String[] args) {
        ModelTesting.test();
        IRepository repository = new Repository();
        Controller controller = new Controller(repository);

        IUserInterface console = new ConsoleUI(repository, controller);
        console.run();
    }
}
