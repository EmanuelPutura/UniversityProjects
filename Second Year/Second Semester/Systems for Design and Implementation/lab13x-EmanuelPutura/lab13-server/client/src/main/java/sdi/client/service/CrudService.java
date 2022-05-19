package sdi.client.service;

import sdi.web.dto.BaseDto;

import java.util.List;

public interface CrudService<T extends BaseDto> {
    List<T> getAll();

    T save(T entity);

    T update(T entity);

    void deleteById(Long id);
}
