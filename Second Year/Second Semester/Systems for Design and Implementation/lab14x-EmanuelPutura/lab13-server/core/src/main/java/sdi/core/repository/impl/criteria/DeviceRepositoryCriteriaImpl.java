package sdi.core.repository.impl.criteria;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.Device;
import sdi.core.repository.custom.DeviceCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("DeviceRepositoryCriteriaImpl")
public class DeviceRepositoryCriteriaImpl extends CustomRepositorySupport implements DeviceCustomRepository {
    private List<Device> getDevicesHavingFieldEqualTo(String fieldName, String value) {
        var entityManager = getEntityManager();
        var criteriaBuilder = entityManager.getCriteriaBuilder();

        var query = criteriaBuilder.createQuery(Device.class);
        query.distinct(true);

        var root = query.from(Device.class);
        query.where(criteriaBuilder.equal(root.get(fieldName), value));

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Device> getDeviceWithType(String type) {
        return getDevicesHavingFieldEqualTo("type", type);
    }

    @Override
    public List<Device> getDeviceWithBrand(String brand) {
        return getDevicesHavingFieldEqualTo("brand", brand);
    }
}
