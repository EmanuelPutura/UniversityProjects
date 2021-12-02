package View;

import Controller.Controller;
import Controller.ControllerException;

public class RunExampleCommand extends Command {
    private Controller controller;
    public RunExampleCommand(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            controller.allStepsExecution();
        } catch (ControllerException error) {
            System.out.println(error.getMessage());
        } catch (Exception error) {
            System.out.println(error.getMessage());
        }
    }
}
