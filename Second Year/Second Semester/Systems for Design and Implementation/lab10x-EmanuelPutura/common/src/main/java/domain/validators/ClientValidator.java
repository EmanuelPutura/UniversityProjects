package domain.validators;

import domain.entities.Client;
import domain.exceptions.ValidatorException;
import utils.IfThenPair;

import java.util.stream.Stream;

/**
 * Validator for Client entities
 */
public class ClientValidator implements Validator<Client> {

    /**
     * Validates an object of type Client
     * @param entity the client to be validated
     * @throws ValidatorException if the client is null
     *                            if any of the client's attributes are null
     *                            if entity.getPhoneNumber() does not return a valid phone number and
     *                            if entity.getEmailAddress() does not contain a @
     */
    @Override
    public void validate(Client entity) throws ValidatorException {
        Stream.of(new IfThenPair(entity == null, "Null entity!"),
                new IfThenPair(entity != null && entity.getId() == null, "Null id!"),
                new IfThenPair(entity != null && entity.getFirstName() == null, "Null first name!"),
                new IfThenPair(entity != null && entity.getLastName() == null, "Null last name!"),
                new IfThenPair(entity != null && entity.getPhoneNumber() == null, "Null phone number!"),
                new IfThenPair(entity != null && !entity.getPhoneNumber().matches("^(\\+4)?0[0-9]{9}$"),
                        "Invalid phone number!"),
                new IfThenPair(entity != null && entity.getEmailAddress() == null, "Null email address!"),
                new IfThenPair(entity != null && !entity.getEmailAddress().contains("@"),
                        "Invalid email address!"),
                new IfThenPair(entity != null && entity.getHomeAddress() == null, "Null home address!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new ValidatorException(elem.getThenError());});
    }
}
