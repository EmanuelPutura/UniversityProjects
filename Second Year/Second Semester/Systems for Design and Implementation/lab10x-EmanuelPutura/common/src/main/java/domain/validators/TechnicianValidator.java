package domain.validators;

import utils.IfThenPair;
import domain.entities.Technician;
import domain.exceptions.ValidatorException;

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
                new IfThenPair(entity != null && entity.getSalary() < 0, "Invalid salary!"),
                new IfThenPair(entity != null && entity.getPhoneNumber() == null, "Null phone number!"),
                new IfThenPair(entity != null && !entity.getPhoneNumber().matches("^(\\+4)?0[0-9]{9}$"),
                        "Invalid phone number!"),
                new IfThenPair(entity != null && entity.getEmailAddress() == null, "Null email!"),
                new IfThenPair(entity != null && !entity.getEmailAddress().contains("@"), "Invalid email!"),
                new IfThenPair(entity != null && entity.getHomeAddress() == null, "Null home address!"),
                new IfThenPair(entity != null && entity.getHomeAddress().isEmpty(), "Empty home address!"),
                new IfThenPair(entity != null && entity.getEmployeeNumber() == null, "Null employee number!"),
                new IfThenPair(entity != null && entity.getEmployeeNumber() < 0, "Invalid employee number!"))
            .filter(IfThenPair::getIfCondition)
            .forEach(elem -> {throw new ValidatorException(elem.getThenError());});
    }
}
