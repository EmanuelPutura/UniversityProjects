package domain.validators;

import domain.entities.Device;
import domain.exceptions.ValidatorException;
import utils.IfThenPair;

import java.util.stream.Stream;

/**
 * Validator for Device entities
 */
public class DeviceValidator implements Validator<Device> {
    /**
     * Validates an entity of type Device
     * @param entity the Device to be validated
     * @throws ValidatorException if the device is null
     *                            if any of the device's attributes are null
     */
    @Override
    public void validate(Device entity) throws ValidatorException {
        Stream.of(new IfThenPair(entity == null, "Null entity!"),
                new IfThenPair(entity != null && entity.getId() == null, "Null id!"),
                new IfThenPair(entity != null && entity.getType() == null, "Null type!"),
                new IfThenPair(entity != null && entity.getBrand() == null, "Null brand!"),
                new IfThenPair(entity != null && entity.getModel() == null, "Null model!"),
                new IfThenPair(entity != null && entity.getClientID() == null, "Null client ID!"))
        .filter(IfThenPair::getIfCondition)
        .forEach(elem -> {throw new ValidatorException(elem.getThenError());});
    }
}
