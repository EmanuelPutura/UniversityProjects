package sdi.core.repository.impl.native_sql;

import org.hibernate.Session;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.Device;
import sdi.core.repository.custom.DeviceCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class DeviceRepositoryNativeSqlImpl extends CustomRepositorySupport implements DeviceCustomRepository {
    @Override
    @Transactional
    public List<Device> getDeviceByType(String type) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Device r where r.type = :type",
                Device.class
        );
        query.setParameter("type", type);

        return query.getResultList();
    }

    @Override
    @Transactional
    public List<Device> getDeviceByBrand(String brand) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Device r where r.brand = :brand",
                Device.class
        );
        query.setParameter("brand", brand);

        return query.getResultList();
    }
}
