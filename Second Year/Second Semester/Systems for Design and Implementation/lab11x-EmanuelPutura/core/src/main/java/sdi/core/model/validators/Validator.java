package sdi.core.model.validators;

import sdi.core.model.exceptions.ValidatorException;

/**
 * Interface for generic Validator
 * @param <T> The type of entity to be validated
 */
public interface Validator<T> {
    void validate(T entity) throws ValidatorException;
}
