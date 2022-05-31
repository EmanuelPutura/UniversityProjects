package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.Device;
import sdi.core.model.entities.Technician;

import java.util.List;

public interface TechnicianRepository extends CatalogRepository<Technician, Long> {
    @Query("select distinct t from Technician t")
    @EntityGraph(value = "Technician.techniciansWithDevices", type = EntityGraph.EntityGraphType.LOAD)
    List<Technician> findAllWithDevices();

    @Query("select distinct t from Technician t")
    @EntityGraph(value = "Technician.techniciansWithDevicesAndClients", type = EntityGraph.EntityGraphType.LOAD)
    List<Technician> findAllWithDevicesAndClients();
}
