package web.lab9.assignment9.service;

import web.lab9.assignment9.exceptions.AppException;

import java.util.Optional;

public interface Service<PK, T> {
    Iterable<T> findAll() throws AppException;

    Optional<T> findOneByPrimaryKey(PK id) throws AppException;
}
