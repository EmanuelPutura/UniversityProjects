package Repository;

import Model.Program.ProgramState;

import java.util.List;

public interface IRepository {
    ProgramState getCurrentProgram() throws RepositoryException;
    List<ProgramState> getProgramStateList();
    void setProgramStateList(List<ProgramState> program_state_list);
    void addProgram(ProgramState program);
}
