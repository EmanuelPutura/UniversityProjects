package sdi.core.repository.custom;

import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientCustomRepository {
    List<Client> getClientsWithFirstName(String firstName);
    List<Client> getClientsWithLastName(String lastName);
}
