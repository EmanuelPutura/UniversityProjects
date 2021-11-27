package Repository;

import Model.Program.ProgramState;

import java.util.List;

public interface IRepository {
    ProgramState getCurrentProgram() throws RepositoryException;
    void setCurrentProgram(ProgramState program);
    List<ProgramState> getProgramStateList();
    void setProgramStateList(List<ProgramState> program_state_list);
    void addProgram(ProgramState program);
    void logProgramStateExec() throws RepositoryException;
    void logProgramStateExec(ProgramState program) throws RepositoryException;
    int size();
}
