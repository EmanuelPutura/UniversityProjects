package sdi.core.service;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import sdi.core.model.entities.Client;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.repository.ClientRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class ClientServiceImpl implements ClientService {
    private final ClientRepository repository;

    @Autowired
    public ClientServiceImpl(ClientRepository repository) {
        this.repository = repository;
    }

    @Override
    public List<Client> getAll() {
        List<Client> resultList = new ArrayList<>();
        repository.findAll().forEach(resultList::add);

        return resultList;
    }

    @Override
    public List<Client> getAllFromPage(int pageNumber, int pageSize) {
        List<Client> resultList = new ArrayList<>();
        repository.findAll(PageRequest.of(pageNumber, pageSize)).forEach(resultList::add);

        return resultList;
    }

    @Override
    public Client save(Client entity) {
        return repository.save(entity);
    }

    @Override
    @Transactional
    public Client update(Client entity) {
        var updatedClient = repository.findById(entity.getId()).orElseThrow();
        updatedClient.setFirstName(entity.getFirstName());
        updatedClient.setLastName(entity.getLastName());
        updatedClient.setEmailAddress(entity.getEmailAddress());

        return updatedClient;
    }

    @Override
    public Optional<Client> search(Long id) {
        return repository.findById(id);
    }

    @Override
    public void delete(Long id) {
        repository.deleteById(id);
    }

    @Override
    public List<Client> findClientsByLastName(String lastName, Sort sort) {
        return repository.findClientsByLastName(lastName, sort);
    }

    @Override
    public Optional<Client> findClientsByAllFieldsButForId(String lastName, String firstName, String emailAddress) {
        var resultList = repository.findClientsByLastNameAndFirstNameAndEmailAddress(lastName, firstName, emailAddress);
        if (resultList.isEmpty()) {
            return Optional.empty();
        }

        return Optional.of(resultList.get(0));
    }
}
