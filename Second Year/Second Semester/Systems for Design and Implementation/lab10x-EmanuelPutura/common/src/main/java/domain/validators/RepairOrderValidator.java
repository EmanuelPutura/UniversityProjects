package domain.validators;

import domain.exceptions.ValidatorException;
import utils.IfThenPair;
import domain.entities.RepairOrder;

import java.util.stream.Stream;

/**
 * Validator for RepairOrder entities
 */
public class RepairOrderValidator implements Validator<RepairOrder> {
    /**
     * Validates an object of type RepairOrder
     * @param entity the order to be validated
     * @throws ValidatorException if entity is null
     *                            if any attributes are null
     *                            if any IDs are negative
     *                            if the cost is negative
     *                            if dates are not (yyyy-mm-dd) format
     */
    @Override
    public void validate(RepairOrder entity) throws ValidatorException {
        Stream.of(new IfThenPair(entity == null, "Null entity!"),
                new IfThenPair(entity != null && entity.getId() == null, "Null id!"),
                new IfThenPair(entity != null && entity.getId() < 0, "Invalid ID!"),
                new IfThenPair(entity != null && entity.getDeviceID() == null, "Null DeviceID!"),
                new IfThenPair(entity != null && entity.getDeviceID() < 0, "Invalid DeviceID!"),
                new IfThenPair(entity != null && entity.getTechnicianID() == null, "Null TechnicianID!"),
                new IfThenPair(entity != null && entity.getTechnicianID() < 0, "Invalid TechnicianID!"),
                new IfThenPair(entity != null && entity.getDateBrought() == null, "Null DateBought!"),
                new IfThenPair(entity != null && !entity.getDateBrought().matches("\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])"),
                        "Invalid DateBought!"),
                new IfThenPair(entity != null && entity.getDateExpected() == null, "Null DateExpected!"),
                new IfThenPair(entity != null && !entity.getDateExpected().matches("\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])"),
                        "Invalid DateExpected!"),
                new IfThenPair(entity != null && entity.getCost() == null, "Null Cost!"),
                new IfThenPair(entity != null && entity.getCost() < 0, "Invalid Cost!"))
        .filter(IfThenPair::getIfCondition)
        .forEach(elem -> {throw new ValidatorException(elem.getThenError());});
    }
}
