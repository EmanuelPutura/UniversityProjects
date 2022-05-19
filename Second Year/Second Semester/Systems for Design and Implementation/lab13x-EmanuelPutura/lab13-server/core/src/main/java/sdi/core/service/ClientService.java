package sdi.core.service;

import org.springframework.data.domain.Sort;
import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientService extends GenericService<Long, Client> {
    List<Client> findClientsByLastName(String lastName, Sort sort);
}
