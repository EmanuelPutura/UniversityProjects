package sdi.core.repository;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import sdi.core.model.Sensor;
import sdi.core.model.SensorNameDto;

import java.util.List;

public interface SensorRepository extends CatalogRepository<Sensor, Long> {
    @Query("select new sdi.core.model.SensorNameDto(s.name) from Sensor s")
    List<SensorNameDto> getAllSensorNames();

    @Query(nativeQuery = true, value = "select * from Sensor s where s.name = :name order by s.time desc limit 4")
    List<Sensor> getSensorDataByName(@Param("name") String name);
}
