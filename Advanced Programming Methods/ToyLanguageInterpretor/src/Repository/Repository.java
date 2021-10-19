package Repository;

import Model.Program.ProgramState;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {
    private List<ProgramState> program_states;

    public Repository() {
        this.program_states = new ArrayList<ProgramState>();
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
    public List<ProgramState> getProgramStateList() {
        return program_states;
    }

    @Override
    public void setProgramStateList(List<ProgramState> program_state_list) {
        program_states = program_state_list;
    }
}
