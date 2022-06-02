package sdi.core.repository;

import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Component;
import sdi.core.model.entities.Client;
import sdi.core.repository.custom.ClientCustomRepository;

import java.util.List;

@Component("ClientRepositoryJpql")
public interface ClientRepository extends CatalogRepository<Client, Long>, ClientCustomRepository {
    List<Client> findClientsByLastName(String lastName, Sort sort);

    @Query("select distinct c from Client c")
    @EntityGraph(value = "Client.clientsWithDevices", type = EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithDevices();

    @Query("select distinct c from Client c")
    @EntityGraph(value = "Client.clientsWithDevicesAndTechnicians", type = EntityGraph.EntityGraphType.LOAD)
    List<Client> findAllWithDevicesAndTechnicians();
}
