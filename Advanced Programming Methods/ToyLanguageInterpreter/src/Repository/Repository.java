package Repository;

import Model.Exceptions.ProgramException;
import Model.Program.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<ProgramState> program_states;
    private String logFilePath;
    private ProgramState initial_state;

    public Repository() {
        this.program_states = new ArrayList<ProgramState>();
    }

    public Repository(String logFilePath) {
        this.program_states = new ArrayList<ProgramState>();
        this.logFilePath = logFilePath;

        try(PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)))) {
            logFile.write("");
        } catch (IOException ignored) {
        }
    }

    public ProgramState getInitialProgramState() {
        return initial_state;
    }

    public Repository(ProgramState initial_state, String logFilePath) {
        this.program_states = new ArrayList<ProgramState>();
        this.program_states.add(initial_state);
        this.logFilePath = logFilePath;
        this.initial_state = initial_state;

        try(PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)))) {
            logFile.write("");
        } catch (IOException ignored) {
        }
    }

    public Repository(List<ProgramState> program_states) {
        this.program_states = program_states;
    }

    @Override
    public List<ProgramState> getProgramStateList() {
        return program_states;
    }

    @Override
    public void setProgramStateList(List<ProgramState> program_state_list) {
        program_states = program_state_list;
    }

    @Override
    public void addProgram(ProgramState program) {
        program_states.add(program);
    }

    @Override
    public void logProgramStateExec(ProgramState program) throws RepositoryException {
        try(PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {
            logFile.write(program.logProgramStateExecution());
        } catch (IOException error) {
            throw new RepositoryException(error.toString());
        }
    }
}
