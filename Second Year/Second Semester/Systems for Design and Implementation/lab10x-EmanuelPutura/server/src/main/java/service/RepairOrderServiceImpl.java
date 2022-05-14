package service;

import domain.entities.RepairOrder;
import domain.entities.Technician;
import domain.exceptions.ConnectionException;
import domain.exceptions.ValidatorException;
import domain.validators.RepairOrderValidator;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;
import repository.RepairOrderRepository;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class RepairOrderServiceImpl implements RepairOrderService {
    private final RepairOrderRepository repairOrderRepository;
    private final ExecutorService executorService;
    private final RepairOrderValidator repairOrderValidator;

    public RepairOrderServiceImpl(RepairOrderRepository repairOrderRepository, ExecutorService executorService) {
        this.repairOrderRepository = repairOrderRepository;
        this.executorService = executorService;

        this.repairOrderValidator = new RepairOrderValidator();
    }

    public Future<List<Technician>> findAllTechnicianWorkingOnDevice(Long deviceId) throws ConnectionException {
        return executorService.submit(() -> {
            return repairOrderRepository.findAllTechnicianWorkingOnDevice(deviceId);
        });
    }

    @Override
    public Future<List<RepairOrder>> findAll() throws ConnectionException {
        return executorService.submit(repairOrderRepository::findAll);
    }

    @Override
    public Future<String> save(RepairOrder entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                repairOrderValidator.validate(entity);
                repairOrderRepository.save(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Repair Order added successfully!";
        });
    }

    @Override
    public Future<String> update(RepairOrder entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                repairOrderValidator.validate(entity);
                repairOrderRepository.update(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Repair Order updated successfully!";
        });
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                repairOrderRepository.deleteById(id);
            } catch (DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Repair Order deleted successfully!";
        });
    }
}
