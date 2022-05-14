package repository;

import domain.BaseEntity;

import java.util.List;

public interface Repository<ID, T extends BaseEntity<ID>> {
    List<T> findAll();

    void save(T entity);

    void update(T entity);

    void deleteById(ID id);
}
