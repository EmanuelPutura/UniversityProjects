package sdi.core.repository.custom;

import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientCustomRepository {
    List<Client> getClientByFirstName(String firstName);
    List<Client> getClientByLastName(String lastName);
}
