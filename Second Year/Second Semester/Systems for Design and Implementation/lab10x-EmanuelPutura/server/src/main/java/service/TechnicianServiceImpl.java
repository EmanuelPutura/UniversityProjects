package service;

import domain.entities.Technician;
import domain.exceptions.ConnectionException;
import domain.exceptions.ValidatorException;
import domain.validators.TechnicianValidator;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;
import repository.TechnicianRepository;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class TechnicianServiceImpl implements TechnicianService {
    private final TechnicianRepository technicianRepository;
    private final ExecutorService executorService;
    private TechnicianValidator technicianValidator;

    public TechnicianServiceImpl(TechnicianRepository technicianRepository, ExecutorService executorService) {
        this.technicianRepository = technicianRepository;
        this.executorService = executorService;

        this.technicianValidator = new TechnicianValidator();
    }

    @Override
    public Future<List<Technician>> findAll() throws ConnectionException {
        return executorService.submit(technicianRepository::findAll);
    }

    @Override
    public Future<String> save(Technician entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                technicianValidator.validate(entity);
                technicianRepository.save(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Technician added successfully!";
        });
    }

    @Override
    public Future<String> update(Technician entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                technicianValidator.validate(entity);
                technicianRepository.update(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Technician updated successfully!";
        });
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                technicianRepository.deleteById(id);
            } catch (DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Technician deleted successfully!";
        });
    }
}
