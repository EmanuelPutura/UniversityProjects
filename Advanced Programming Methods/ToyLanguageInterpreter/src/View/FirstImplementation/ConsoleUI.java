package View.FirstImplementation;

import Controller.Controller;
import Model.Exceptions.EmptyExecutionStackException;
import Model.Exceptions.InvalidIndexException;
import Controller.ControllerException;
import Model.Program.ProgramState;
import Repository.IRepository;

import java.util.List;
import java.util.Scanner;

import static View.FirstImplementation.ConsoleColors.*;

public class ConsoleUI implements IUserInterface {
    private IRepository repository;
    private Controller controller;

    public ConsoleUI(IRepository repository, Controller controller) {
        this.repository = repository;
        this.controller = controller;
    }

    private void addDefaultPrograms(Scanner scanner) {
        System.out.println("Do you want to add default programs into the repository? [Y/n]");
        System.out.print(ANSI_GREEN + "command >> " + ANSI_RESET);
        String answer = scanner.nextLine();

        while (!answer.equals("Y") && !answer.equals("n")) {
            System.out.println(ANSI_RED + "Error: Please provide a valid response." + ANSI_RESET);
            System.out.print(ANSI_GREEN + "command >> " + ANSI_RESET);
            answer = scanner.nextLine();
        }

        if (answer.equals("Y")) {
            DefaultTestPrograms.addAll(repository);
            System.out.println(ANSI_GREEN + "...adding default programs to the repository" + ANSI_RESET);
        }
    }

    private void menu() {
        final String TITLE = '\n' + ANSI_WHITE_BACKGROUND + " Toy Language Interpreter [assignment 2] " + ANSI_RESET;
        System.out.println(TITLE);
        System.out.println(ANSI_GREEN + ">> " + ANSI_RESET + "exec [--one | --all] [PROGRAM NO] - execute a default program");
        System.out.println(ANSI_GREEN + ">> " + ANSI_RESET + "list [--default | --statement] - lists all the default programs");
        System.out.println(ANSI_GREEN + ">> " + ANSI_RESET + "exit - exit the application\n");
    }

    private String getMenuCommand(Scanner scanner) {
        System.out.print(ANSI_GREEN + "command >> " + ANSI_RESET);
        return scanner.nextLine();
    }

    private void executeOneStep(int index) throws UIException {
        try {
            controller.setAndSwapCurrentProgram(index);
            controller.oneStepExecution(true, true);
            controller.setAndSwapCurrentProgram(index);
        } catch (InvalidIndexException exception) {
            throw new UIException(exception.getMessage());
        } catch (ControllerException exception) {
            throw new UIException(exception.getMessage());
        } catch (EmptyExecutionStackException exception) {
            throw new UIException(exception.getMessage());
        }
    }

    private void executeAllSteps(int index) throws UIException {
        try {
            controller.setAndSwapCurrentProgram(index);
            controller.allStepsExecution(true);
            controller.setAndSwapCurrentProgram(index);
        } catch (InvalidIndexException exception) {
            throw new UIException(exception.getMessage());
        } catch (ControllerException exception) {
            throw new UIException(exception.getMessage());
        } catch (EmptyExecutionStackException exception) {
            throw new UIException(exception.getMessage());
        }
    }

    private void listAllDefaultPrograms() {
        List<ProgramState> states = controller.getAllProgramStates();

        for (int i = 0; i < repository.size(); ++i) {
            System.out.printf("%d. ", i + 1);
            System.out.print(states.get(i).toString());
            System.out.println();
        }
    }

    private void listAllStatements() {
        List<ProgramState> states = controller.getAllProgramStates();

        for (int i = 0; i < repository.size(); ++i) {
            System.out.printf("%d. ", i + 1);
            System.out.print(states.get(i).getInitialStatement().toString());
            System.out.println();
        }
    }

    @Override
    public void run() {
        Scanner scanner = new Scanner(System.in);
        boolean running = true;
        addDefaultPrograms(scanner);

        while (running) {
            try {
                menu();

                String command = getMenuCommand(scanner);
                if (command.matches("^exec.*")) {
                    if (command.matches("^exec --one [1-6]")) {
                        executeOneStep(command.charAt(command.length() - 1) - '0' - 1);
                    } else if (command.matches("^exec --all [1-6]")) {
                        executeAllSteps(command.charAt(command.length() - 1) - '0' - 1);
                    } else {
                        System.out.println(ANSI_RED + "Invalid exec argument!" + ANSI_RESET);
                        continue;
                    }
                } else if (command.equals("list --default")) {
                    listAllDefaultPrograms();
                } else if (command.equals("list --statement")) {
                    listAllStatements();
                } else if (command.equals("exit"))
                    running = false;
                else {
                    System.out.println(ANSI_RED + String.format("'%s' is not a valid command!", command) + ANSI_RESET);
                    continue;
                }
            } catch (UIException exception) {
                System.out.println(ANSI_RED + "Error: " + exception.getMessage() + ANSI_RESET);
            } catch (Exception exception) {
                System.out.println(ANSI_RED + "Error: " + exception.getMessage() + ANSI_RESET);
            }
        }
    }
}
