package domain.entities;

import domain.BaseEntity;
import utils.IfThenPair;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Stream;

public class RepairOrder extends BaseEntity<Long> {
    private Long deviceID;
    private Long technicianID;
    private String dateBrought;
    private String dateExpected;
    private Float cost;

    /**
     * Creates a new RepairOrder object
     *
     * @param ID           the ID of the repair order, cannot be null, cannot be negative
     * @param deviceID     the device id, cannot be null, cannot be negative
     * @param technicianID the id of the technician, cannot be null, cannot be negative
     * @param dateBrought   date order was placed, cannot be null, yyyy-mm-dd format
     * @param dateExpected date order is expected to finish, cannot be null, yyyy-mm-dd format
     * @param cost         order cost, cannot be null, cannot be negative
     */
    public RepairOrder(Long ID, Long deviceID, Long technicianID, String dateBrought, String dateExpected, float cost) {
        this.setId(ID);
        this.deviceID = deviceID;
        this.technicianID = technicianID;
        this.dateBrought = dateBrought;
        this.dateExpected = dateExpected;
        this.cost = cost;
    }

    /**
     * Gets the device id from the repair order.
     *
     * @return a {@code Long} - deviceID
     */
    public Long getDeviceID() {
        return deviceID;
    }

    /**
     * Sets the device id from the repair order to the given value.
     *
     * @param deviceID - new device id
     * @throws IllegalArgumentException if deviceID is null or negative
     */
    public void setDeviceID(Long deviceID) {
        Stream.of(new IfThenPair(deviceID==null, "Device ID cannot be null!"),
                        new IfThenPair(deviceID!=null && deviceID < 0, "Device ID cannot be negative"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.deviceID = deviceID;
    }

    /**
     * Gets the technician id from the repair order.
     *
     * @return a {@code Long} - technicianID
     */
    public Long getTechnicianID() {
        return technicianID;
    }

    /**
     * Sets the technician id from the repair order to the given value.
     *
     * @param technicianID - new technician id
     * @throws IllegalArgumentException if technicianID is null or negative
     */
    public void setTechnicianID(Long technicianID) {
        Stream.of(new IfThenPair(technicianID==null, "Technician ID cannot be null!"),
                        new IfThenPair(technicianID!=null && technicianID < 0, "Technician ID cannot be negative"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.technicianID = technicianID;
    }

    /**
     * Gets the buy date from the repair order.
     *
     * @return a {@code String} - dateBought
     */
    public String getDateBrought() {
        return dateBrought;
    }

    /**
     * Sets the buy date from the repair order to the given value.
     *
     * @param dateBrought - new buy date
     * @throws IllegalArgumentException if dateBought is null or not valid (yyyy-mm-dd)
     */
    public void setDateBrought(String dateBrought) {
        Stream.of(new IfThenPair(dateBrought ==null, "Buy date cannot be null!"),
                        new IfThenPair(dateBrought !=null && !dateBrought.matches("\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])"),
                                "Buy date invalid (must be yyyy-mm-dd)"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.dateBrought = dateBrought;
    }

    /**
     * Gets the expected date from the repair order.
     *
     * @return a {@code String} - dateExpected
     */
    public String getDateExpected() {
        return dateExpected;
    }

    /**
     * Sets the expected date from the repair order to the given value.
     *
     * @param dateExpected - new expected date
     * @throws IllegalArgumentException if dateExpected is null or not valid (yyyy-mm-dd)
     */
    public void setDateExpected(String dateExpected) {
        Stream.of(new IfThenPair(dateExpected==null, "Expected date cannot be null!"),
                        new IfThenPair(dateExpected!=null && !dateExpected.matches("\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])"),
                                "Expected date invalid (must be yyyy-mm-dd)"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.dateExpected = dateExpected;
    }

    /**
     * Gets the cost from the repair order.
     *
     * @return a {@code Long} - cost
     */
    public Float getCost() {
        return cost;
    }

    /**
     * Sets the costs of the repair order to the given value.
     *
     * @param cost - new cost
     * @throws IllegalArgumentException if cost is null or negative
     */
    public void setCost(Float cost) {
        Stream.of(new IfThenPair(cost==null, "Cost cannot be null!"),
                        new IfThenPair(cost!=null && cost < 0, "Cost cannot be negative"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.cost = cost;
    }

    @Override
    public String toString() {
        return "RepairOrder{" +
                "repairID=" + this.getId() +
                ", deviceID=" + deviceID +
                ", technicianID=" + technicianID +
                ", dateBought='" + dateBrought + '\'' +
                ", dateExpected='" + dateExpected + '\'' +
                ", cost=" + cost +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RepairOrder that = (RepairOrder) o;
        return Float.compare(that.cost, cost) == 0 && deviceID.equals(that.deviceID) && technicianID.equals(that.technicianID) && Objects.equals(dateBrought, that.dateBrought) && Objects.equals(dateExpected, that.dateExpected);
    }

    @Override
    public int hashCode() {
        return Objects.hash(deviceID, technicianID, dateBrought, dateExpected, cost);
    }

    public static List<RepairOrder> readFromFile(String filePath, String delimiter) throws FileNotFoundException, IllegalArgumentException {
        List<RepairOrder> repairOrders = new Vector<>();
        Scanner fileScanner = new Scanner(new File(filePath));
        fileScanner.useDelimiter(delimiter);
        Long id, deviceID, technicianID;
        String dateBrought, dateExpected;
        Float cost;
        while (fileScanner.hasNext()) {
            id = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a repairOrder must be a positive integer!"));
            deviceID = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a repairOrder must be a positive integer!"));
            technicianID = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a repairOrder must be a positive integer!"));
            dateBrought = fileScanner.next();
            dateExpected = fileScanner.next();
            cost = Optional.of(fileScanner).filter(Scanner::hasNextFloat).map(Scanner::next).map(Float::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The cost of a repairOrder must be a positive number!"));
            fileScanner.nextLine();
            repairOrders.add(new RepairOrder(id, deviceID, technicianID, dateBrought, dateExpected, cost));
        }
        return repairOrders;
    }


}
