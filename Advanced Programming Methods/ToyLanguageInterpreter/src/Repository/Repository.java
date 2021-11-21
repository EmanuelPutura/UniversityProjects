package Repository;

import Model.Exceptions.DictionaryException;
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

    public Repository(ProgramState initial_state, String logFilePath) {
        this.program_states = new ArrayList<ProgramState>();
        this.program_states.add(initial_state);
        this.logFilePath = logFilePath;

        try(PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, false)))) {
            logFile.write("");
        } catch (IOException ignored) {
        }
    }

    public Repository(List<ProgramState> program_states) {
        this.program_states = program_states;
    }

    @Override
    public ProgramState getCurrentProgram() throws RepositoryException {
        if (program_states.size() == 0)
            throw new RepositoryException("There is no program loaded into the repository!");
        return program_states.get(program_states.size() - 1);
    }

    @Override
    public void setCurrentProgram(ProgramState program) {
        program_states.set(program_states.size() - 1, program);
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
    public void logProgramStateExec() throws RepositoryException {
        try(PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)))) {
            logFile.write(getCurrentProgram().toFileString());
        } catch (IOException | ProgramException error) {
            throw new RepositoryException(error.toString());
        }
    }

    @Override
    public int size() {
        return program_states.size();
    }
}
