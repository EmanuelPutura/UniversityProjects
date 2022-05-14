package service;

import domain.entities.Client;

public interface ClientService extends GenericService<Long, Client> {
    String GET_ALL = "getClients";
    String SAVE_ONE = "saveClient";
    String UPDATE_ONE = "updateClient";
    String DELETE_ONE = "deleteClient";
}
