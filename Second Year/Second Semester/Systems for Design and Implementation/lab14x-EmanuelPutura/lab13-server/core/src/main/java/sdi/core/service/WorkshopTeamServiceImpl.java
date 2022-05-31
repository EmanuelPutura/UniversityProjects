package sdi.core.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.WorkshopTeamRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class WorkshopTeamServiceImpl implements WorkshopTeamService {
    private final WorkshopTeamRepository repository;

    @Autowired
    public WorkshopTeamServiceImpl(WorkshopTeamRepository repository) {
        this.repository = repository;
    }

    @Override
    public List<WorkshopTeam> getAll() {
        List<WorkshopTeam> resultList = new ArrayList<>();
        repository.findAll().forEach(resultList::add);

        return resultList;
    }

    @Override
    public List<WorkshopTeam> getAllFromPage(int pageNumber, int pageSize) {
        List<WorkshopTeam> resultList = new ArrayList<>();
        repository.findAll(PageRequest.of(pageNumber, pageSize)).forEach(resultList::add);

        return resultList;
    }

    @Override
    public WorkshopTeam save(WorkshopTeam entity) {
        return repository.save(entity);
    }

    @Override
    @Transactional
    public WorkshopTeam update(WorkshopTeam entity) {
        var updatedTeam = repository.findById(entity.getId()).orElseThrow();
        updatedTeam.setTeamName(entity.getTeamName());
        updatedTeam.setTeamTechnician(entity.getTeamTechnician());

        return updatedTeam;
    }

    @Override
    public Optional<WorkshopTeam> search(Long id) {
        return repository.findById(id);
    }

    @Override
    public void delete(Long id) {
        repository.deleteById(id);
    }
}
