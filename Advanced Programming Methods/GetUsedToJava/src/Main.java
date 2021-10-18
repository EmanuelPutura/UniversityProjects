/*
    Problem Statement:
    1. Intr-o parcare exista masini, motociclete si biciclete. Sa se afiseze toate vehiculele de culoare rosie.
*/

import Controller.Controller;
import Repository.Repository;
import Repository.IRepository;
import Testing.RepositoryTesting;
import View.ConsoleUI;

public class Main {
    public static void main(String[] args) {
        RepositoryTesting.test();

        IRepository repository = new Repository();
        Controller controller = new Controller(repository);
        ConsoleUI console = new ConsoleUI(controller);
        console.run();
    }
}
