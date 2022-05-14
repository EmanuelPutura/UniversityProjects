package web.lab9.assignment9.repository;

import web.lab9.assignment9.exceptions.AppException;

import java.util.Optional;
import java.util.ResourceBundle;

public interface Repository<PK, T> {
    Iterable<T> findAll() throws AppException;

    Optional<T> findOneByPrimaryKey(PK id) throws AppException;
}
