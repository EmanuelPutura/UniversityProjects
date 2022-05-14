package service;

import domain.BaseEntity;
import domain.exceptions.ConnectionException;

import java.util.List;
import java.util.concurrent.Future;

public interface GenericService<ID, T extends BaseEntity<ID>> {
    Future<List<T>> findAll() throws ConnectionException;

    Future<String> save(T entity) throws ConnectionException;

    Future<String> update(T entity) throws ConnectionException;

    Future<String> deleteById(ID id) throws ConnectionException;
}
