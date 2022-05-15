package web.lab9.assignment9.repository;

import web.lab9.assignment9.exceptions.AppException;

import java.util.List;
import java.util.Optional;

public interface Repository<PK, T> {
    List<T> findAll() throws AppException;

    Optional<T> findOneByPrimaryKey(PK id) throws AppException;

    void save(T entity) throws AppException;
}
