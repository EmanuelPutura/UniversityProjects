package Repository;

import Model.Program.ProgramState;

import java.util.List;

public interface IRepository {
    List<ProgramState> getProgramStateList();
    void setProgramStateList(List<ProgramState> program_state_list);
    void addProgram(ProgramState program);
    void logProgramStateExec(ProgramState program) throws RepositoryException;
    ProgramState getInitialProgramState();
}
