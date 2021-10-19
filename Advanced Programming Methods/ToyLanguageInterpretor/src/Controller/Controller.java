package Controller;

import Model.DataStructures.IADTStack;
import Model.Exceptions.EmptyExecutionStackException;
import Model.Exceptions.StackException;
import Model.Exceptions.StatementException;
import Model.Exceptions.UndeclaredVariableException;
import Model.Program.ProgramState;
import Model.Statements.IStatement;
import Repository.IRepository;
import Repository.RepositoryException;

public class Controller {
    private IRepository repository;
    private String execution_logs;

    public Controller(IRepository repository) {
        this.repository = repository;
        this.execution_logs = "";
    }

    public void addProgram(ProgramState program) {
        repository.addProgram(program);
        this.execution_logs = "";
    }

    public String logs() {
        return execution_logs;
    }

    private void resetLogs() {
        execution_logs = "";
    }

    public ProgramState oneStepExecution(boolean reset_logs) throws ControllerException, EmptyExecutionStackException {
        if (reset_logs)
            resetLogs();

        ProgramState program = null;
        try {
            program = repository.getCurrentProgram();
        } catch (RepositoryException exception) {
            throw new ControllerException(exception.getMessage());
        }

        return oneStepExecution(program, reset_logs);
    }

    public ProgramState oneStepExecution(ProgramState program, boolean reset_logs) throws ControllerException, EmptyExecutionStackException {
        if (program == null)
            throw new ControllerException("Invalid program state!");
        if (reset_logs)
            resetLogs();

        IADTStack<IStatement> execution_stack = program.executionStack();
        if (execution_stack.empty())
            throw new EmptyExecutionStackException("Empty execution stack error!");

        execution_logs = String.format("Initial program state: %s\n", program.toString());
        IStatement to_execute;

        try {
            to_execute = execution_stack.pop();
        } catch (StackException exception) {
            throw new ControllerException(exception.getMessage());
        }

        try {
            ProgramState return_state = to_execute.execute(program);
            execution_logs += String.format("Current program state: %s", return_state.toString());
            return return_state;
        } catch (StatementException | UndeclaredVariableException exception) {
            throw new ControllerException(exception.getMessage());
        }
    }

    public void allStepsExecution() throws ControllerException, EmptyExecutionStackException {
        resetLogs();
        ProgramState program = null;
        try {
            program = repository.getCurrentProgram();
        } catch (RepositoryException exception) {
            throw new ControllerException(exception.getMessage());
        }

        allStepsExecution(program);
    }

    public void allStepsExecution(ProgramState program) throws ControllerException, EmptyExecutionStackException {
        if (program == null)
            throw new ControllerException("Invalid program state!");

        resetLogs();
        IADTStack<IStatement> execution_stack = program.executionStack();
        if (execution_stack.empty())
            throw new EmptyExecutionStackException("Empty execution stack error!");

        StringBuilder string_builder = new StringBuilder(String.format("Initial program state: %s\n", program.toString()));

        while (!execution_stack.empty()) {
            oneStepExecution(program, false);
            string_builder.append(String.format("Current program state: %s\n", program.toString()));
        }

        execution_logs = string_builder.toString();
    }
}
