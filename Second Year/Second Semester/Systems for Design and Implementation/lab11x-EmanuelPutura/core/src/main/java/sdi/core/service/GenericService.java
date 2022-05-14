package sdi.core.service;

import sdi.core.model.BaseEntity;

import java.io.Serializable;
import java.util.List;
import java.util.Optional;

public interface GenericService<ID extends Serializable, T extends BaseEntity<ID>> {
    List<T> getAll();

    T save(T entity);

    T update(T entity);

    Optional<T> search(ID id);

    void delete(ID id);
}
