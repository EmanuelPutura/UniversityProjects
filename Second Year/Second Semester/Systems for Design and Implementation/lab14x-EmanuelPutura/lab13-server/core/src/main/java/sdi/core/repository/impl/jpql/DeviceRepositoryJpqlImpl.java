package sdi.core.repository.impl.jpql;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.Device;
import sdi.core.repository.custom.DeviceCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("DeviceRepositoryJpqlImpl")
public class DeviceRepositoryJpqlImpl extends CustomRepositorySupport implements DeviceCustomRepository {
    private List<Device> getClientsWithFieldEqualTo(String field, String value, String queryString) {
        var entityManager = getEntityManager();

        var query = entityManager.createQuery(
                queryString, Device.class
        );
        query.setParameter(field, value);

        return query.getResultList();
    }

    @Override
    public List<Device> getDeviceWithType(String type) {
        String queryString = "select distinct r from Device r where r.type = :type";
        return getClientsWithFieldEqualTo("type", type, queryString);
    }

    @Override
    public List<Device> getDeviceWithBrand(String brand) {
        String queryString = "select distinct r from Device r where r.brand = :brand";
        return getClientsWithFieldEqualTo("brand", brand, queryString);
    }
}
