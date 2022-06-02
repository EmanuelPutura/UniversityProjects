package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Component;
import sdi.core.model.entities.Device;
import sdi.core.model.entities.Technician;
import sdi.core.repository.custom.TechnicianCustomRepository;

import java.util.List;

@Component("TechnicianRepositoryJpql")
public interface TechnicianRepository extends CatalogRepository<Technician, Long>, TechnicianCustomRepository {
    @Query("select distinct t from Technician t")
    @EntityGraph(value = "Technician.techniciansWithDevices", type = EntityGraph.EntityGraphType.LOAD)
    List<Technician> findAllWithDevices();

    @Query("select distinct t from Technician t")
    @EntityGraph(value = "Technician.techniciansWithDevicesAndClients", type = EntityGraph.EntityGraphType.LOAD)
    List<Technician> findAllWithDevicesAndClients();
}
