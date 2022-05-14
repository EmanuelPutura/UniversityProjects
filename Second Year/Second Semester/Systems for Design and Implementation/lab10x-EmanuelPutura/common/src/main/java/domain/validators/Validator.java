package domain.validators;

import domain.exceptions.ValidatorException;

/**
 * Interface for generic Validator
 * @param <T> The type of entity to be validated
 */
public interface Validator<T> {
    void validate(T entity) throws ValidatorException;
}
