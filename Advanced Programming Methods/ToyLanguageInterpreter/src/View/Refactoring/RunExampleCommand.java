package View.Refactoring;

import Controller.Controller;
import Controller.ControllerException;
import Model.Exceptions.EmptyExecutionStackException;
import Model.Exceptions.InvalidIndexException;
import View.FirstImplementation.UIException;

public class RunExampleCommand extends Command {
    private Controller controller;
    public RunExampleCommand(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            controller.allStepsExecution(true);
        } catch (EmptyExecutionStackException | ControllerException error) {
            System.out.println(error.getMessage());
        } catch (Exception error) {
            System.out.println(error.getMessage());
        }
    }
}
