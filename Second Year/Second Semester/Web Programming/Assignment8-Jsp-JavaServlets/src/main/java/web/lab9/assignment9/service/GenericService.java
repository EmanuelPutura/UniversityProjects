package web.lab9.assignment9.service;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.repository.Repository;

import java.util.Optional;

public abstract class GenericService<PK, T> implements Service<PK, T> {
    protected final Repository<PK, T> repository;

    public GenericService(Repository<PK, T> repository) {
        this.repository = repository;
    }

    @Override
    public Iterable<T> findAll() throws AppException {
        return repository.findAll();
    }

    @Override
    public Optional<T> findOneByPrimaryKey(PK id) throws AppException {
        return repository.findOneByPrimaryKey(id);
    }
}
