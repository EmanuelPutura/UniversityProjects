package web.lab9.assignment9.repository;

import web.lab9.assignment9.exceptions.RepositoryException;

import java.util.Optional;

public interface Repository<PK, T> {
    String PROPERTIES_FILE_PATH = "./resources/database.properties";

    Iterable<T> findAll() throws RepositoryException;

    Optional<T> findOneByPrimaryKey(PK id) throws RepositoryException;
}
