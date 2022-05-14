package domain.entities;

import domain.BaseEntity;
import utils.IfThenPair;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Stream;

public class Device extends BaseEntity<Long> {
    private String type;
    private String brand;
    private String model;
    private Long clientID;

    /**
     * Creates a new object of type Device
     * @param id The ID of the Device, must be not null
     * @param type The type of the Device, must be not null
     * @param brand The brand of the Device, must be not null
     * @param model The model of the Device, must be not null
     * @param clientID The ID of the client that owns the device, must be not null
     */
    public Device(Long id, String type, String brand, String model, Long clientID) {
        this.setId(id);
        this.type = type;
        this.brand = brand;
        this.model = model;
        this.clientID = clientID;
    }

    /**
     * Returns the type of the device
     * @return A {@code String} representing the device's type
     */
    public String getType() {
        return type;
    }

    /**
     * Sets the type of the device
     * @param type The new type
     * @throws IllegalArgumentException if type is null
     */
    public void setType(String type) {
        Stream.of(new IfThenPair(type == null, "Type cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.type = type;
    }

    /**
     * Returns the brand of the device
     * @return A {@code String} representing the device's brand
     */
    public String getBrand() {
        return brand;
    }

    /**
     * Sets the brand of the device
     * @param brand The new brand
     * @throws IllegalArgumentException if brand is null
     */
    public void setBrand(String brand) {
        Stream.of(new IfThenPair(brand == null, "Brand cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.brand = brand;
    }

    /**
     * Returns the model of the device
     * @return A {@code String} representing the device's model
     */
    public String getModel() {
        return model;
    }

    /**
     * Sets the model of the device
     * @param model The new model
     * @throws IllegalArgumentException if model is null
     */
    public void setModel(String model) {
        Stream.of(new IfThenPair(model == null, "Model cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.model = model;
    }

    /**
     * Returns the ID of the owner of the device
     * @return A {@code Long} representing the device's client ID
     */
    public Long getClientID() {
        return clientID;
    }

    /**
     * Sets the client ID of the device
     * @param clientID The new client ID
     * @throws IllegalArgumentException if clientID is null
     */
    public void setClientID(Long clientID) {
        Stream.of(new IfThenPair(clientID == null, "Client ID cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.clientID = clientID;
    }

    /**
     * Represents the device as a string
     * @return The {@code String} representation of the device.
     */
    @Override
    public String toString() {
        return "Device{" +
                "id=" + this.getId() +
                ", type='" + type + '\'' +
                ", brand='" + brand + '\'' +
                ", model='" + model + '\'' +
                ", clientID=" + clientID +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Device device = (Device) o;
        return type.equals(device.type) && brand.equals(device.brand) && model.equals(device.model)
                && clientID.equals(device.clientID);
    }

    @Override
    public int hashCode() {
        return Objects.hash(type, brand, model, clientID);
    }

    public static List<Device> readFromFile(String filePath, String delimiter) throws FileNotFoundException, IllegalArgumentException {
        List<Device> devices = new Vector<>();
        Scanner fileScanner = new Scanner(new File(filePath));
        fileScanner.useDelimiter(delimiter);
        Long id, clientID;
        String type, brand, model;
        while (fileScanner.hasNext()) {
            id = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
            type = fileScanner.next();
            brand = fileScanner.next();
            model = fileScanner.next();
            clientID = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
            fileScanner.nextLine();
            devices.add(new Device(id, type, brand, model, clientID));
        }
        return devices;
    }
}
