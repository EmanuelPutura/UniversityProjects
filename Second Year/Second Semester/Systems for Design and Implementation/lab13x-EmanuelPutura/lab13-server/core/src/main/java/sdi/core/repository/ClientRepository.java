package sdi.core.repository;

import org.springframework.data.domain.Sort;
import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientRepository extends CatalogRepository<Client, Long> {
    List<Client> findClientsByLastName(String lastName, Sort sort);

    List<Client> findClientsByLastNameAndFirstNameAndEmailAddress(String lastName, String firstName, String emailAddress);
}
