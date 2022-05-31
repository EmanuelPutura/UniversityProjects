package sdi.core.repository.impl.criteria;

import sdi.core.model.entities.Device;
import sdi.core.repository.custom.DeviceCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

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
    public List<Device> getDevicesWithType(String type) {
        return getDevicesHavingFieldEqualTo("type", type);
    }

    @Override
    public List<Device> getDevicesWithBrand(String brand) {
        return getDevicesHavingFieldEqualTo("brand", brand);
    }
}
