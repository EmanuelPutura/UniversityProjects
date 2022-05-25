package sdi.core.service;

import org.springframework.data.domain.Sort;
import sdi.core.model.entities.Client;

import java.util.List;
import java.util.Optional;

public interface ClientService extends GenericService<Long, Client> {
    List<Client> findClientsByLastName(String lastName, Sort sort);

    Optional<Client> findClientsByAllFieldsButForId(String lastName, String firstName, String emailAddress);
}
