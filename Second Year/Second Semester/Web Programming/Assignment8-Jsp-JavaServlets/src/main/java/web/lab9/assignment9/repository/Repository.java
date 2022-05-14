package web.lab9.assignment9.repository;

import web.lab9.assignment9.exceptions.AppException;

import java.util.Optional;

public interface Repository<PK, T> {
    String PROPERTIES_FILE_PATH = "./resources/database.properties";

    Iterable<T> findAll() throws AppException;

    Optional<T> findOneByPrimaryKey(PK id) throws AppException;
}
