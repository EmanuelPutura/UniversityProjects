package service;

import domain.entities.Client;
import domain.exceptions.ConnectionException;
import domain.exceptions.ValidatorException;
import domain.validators.ClientValidator;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;
import repository.ClientRepository;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class ClientServiceImpl implements ClientService {
    private final ClientRepository clientRepository;
    private final ExecutorService executorService;
    private final ClientValidator clientValidator;

    public ClientServiceImpl(ClientRepository clientRepository, ExecutorService executorService) {
        this.clientRepository = clientRepository;
        this.executorService = executorService;

        this.clientValidator = new ClientValidator();
    }

    @Override
    public Future<List<Client>> findAll() throws ConnectionException {
        return executorService.submit(clientRepository::findAll);
    }

    @Override
    public Future<String> save(Client entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                clientValidator.validate(entity);
                clientRepository.save(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Client added successfully!";
        });
    }

    @Override
    public Future<String> update(Client entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                clientValidator.validate(entity);
                clientRepository.update(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Client updated successfully!";
        });
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                clientRepository.deleteById(id);
            } catch (DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Client deleted successfully!";
        });
    }
}
