package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.Device;
import sdi.core.repository.custom.DeviceCustomRepository;

import java.util.List;

public interface DeviceRepository extends CatalogRepository<Device, Long>, DeviceCustomRepository {
    @EntityGraph(value = "Device.devicesWithTechniciansAndClient", type = EntityGraph.EntityGraphType.LOAD)
    List<Device> findDeviceByClientId(Long clientId);

    @Query("select distinct d from Device d")
    @EntityGraph(value = "Device.devicesWithTechnicians", type = EntityGraph.EntityGraphType.LOAD)
    List<Device> findAllWithTechnicians();

    @Query("select distinct d from Device d")
    @EntityGraph(value = "Device.devicesWithClient", type = EntityGraph.EntityGraphType.LOAD)
    List<Device> findAllWithClient();

    @Query("select distinct d from Device d")
    @EntityGraph(value = "Device.devicesWithTechniciansAndClient", type = EntityGraph.EntityGraphType.LOAD)
    List<Device> findAllWithTechniciansAndClient();
}
