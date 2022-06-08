package sdi.sensors.repository;

import sdi.sensors.domain.BaseEntity;

import java.util.List;
import java.util.Optional;

public interface Repository<ID, T extends BaseEntity<ID>> {
    List<T> findAll();

    Optional<T> findById(ID id);

    Optional<T> findByName(String name);

    void save(T entity);
}
