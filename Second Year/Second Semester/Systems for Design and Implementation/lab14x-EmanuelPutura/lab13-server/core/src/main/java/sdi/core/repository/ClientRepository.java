package sdi.core.repository;

import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.Client;

import java.util.List;

public interface ClientRepository extends CatalogRepository<Client, Long> {
    List<Client> findClientsByLastName(String lastName, Sort sort);

    @Query("select distinct c from Client c")
    @EntityGraph(value = "Client.clientsWithDevices", type = EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithDevices();

    @Query("select distinct c from Client c")
    @EntityGraph(value = "Client.clientsWithDevicesAndTechnicians", type = EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithDevicesAndTechnicians();
}
