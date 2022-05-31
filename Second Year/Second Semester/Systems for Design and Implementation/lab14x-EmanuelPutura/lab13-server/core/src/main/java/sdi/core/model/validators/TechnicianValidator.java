package sdi.core.model.validators;

import sdi.core.model.entities.IfThenPair;
import sdi.core.model.entities.Technician;
import sdi.core.model.exceptions.ValidatorException;

import java.util.stream.Stream;

/**
 * Validator for Technician entities
 */
public class TechnicianValidator implements Validator<Technician> {

    /**
     * Validates an object of type Technician
     * @param entity the technician to be validated
     * @throws ValidatorException if technician is null
     *                            if any attributes are null
     *                            if any strings are empty
     *                            if the id is negative
     *                            if the salary is negative
     *                            if the phone number is invalid
     *                            if the email does not contain a @
     *                            if the number of employees is negative
     */
    @Override
    public void validate(Technician entity) throws ValidatorException {
        Stream.of(new IfThenPair(entity == null, "Null entity!"),
                new IfThenPair(entity != null && entity.getId() == null, "Null id!"),
                new IfThenPair(entity != null && entity.getId() < 0, "Invalid ID!"),
                new IfThenPair(entity != null && entity.getFirstName() == null, "Null first name!"),
                new IfThenPair(entity != null && entity.getFirstName().isEmpty(), "Empty first name!"),
                new IfThenPair(entity != null && entity.getLastName() == null, "Null last name!"),
                new IfThenPair(entity != null && entity.getLastName().isEmpty(), "Empty last name!"),
                new IfThenPair(entity != null && entity.getSalary() == null, "Null salary!"),
                new IfThenPair(entity != null && entity.getSalary() < 0, "Invalid salary!"))
            .filter(IfThenPair::getIfCondition)
            .forEach(elem -> {throw new ValidatorException(elem.getThenError());});
    }
}
