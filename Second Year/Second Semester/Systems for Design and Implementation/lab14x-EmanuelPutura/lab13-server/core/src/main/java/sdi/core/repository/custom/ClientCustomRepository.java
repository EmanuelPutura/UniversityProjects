package sdi.core.repository.custom;

import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientCustomRepository {
    List<Client> getClientWithFirstName(String firstName);
    List<Client> getClientWithLastName(String lastName);
}
