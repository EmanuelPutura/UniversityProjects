package domain.entities;

import domain.BaseEntity;
import utils.IfThenPair;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Stream;

public class Client extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private String phoneNumber;
    private String emailAddress;
    private String homeAddress;

    /**
     * Creates a new object of type Client
     * @param id the id of the client, must not be null
     * @param firstName the first name, must not be null
     * @param lastName the last name, must not be null
     * @param phoneNumber the phone number, must not be null, must be a valid phone number
     *                    (10 numbers, optional regional code)
     * @param emailAddress the email address, must not be null, must be a valid email address (contains @)
     * @param homeAddress the home address, must not be null
     */
    public Client(Long id, String firstName, String lastName, String phoneNumber, String emailAddress,
                  String homeAddress) {
        this.setId(id);
        this.firstName = firstName;
        this.lastName = lastName;
        this.phoneNumber = phoneNumber;
        this.emailAddress = emailAddress;
        this.homeAddress = homeAddress;
    }

    /**
     * Returns the first name of the client
     * @return A {@code String} representing the client's first name
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets the first name of the client
     * @param firstName The new first name
     * @throws IllegalArgumentException if firstName is null
     */
    public void setFirstName(String firstName) {
        Stream.of(new IfThenPair(firstName == null, "First name cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.firstName = firstName;
    }

    /**
     * Returns the last name of the client
     * @return A {@code String} representing the client's last name
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets the last name of the client
     * @param lastName The new last name
     * @throws IllegalArgumentException if lastName is null
     */
    public void setLastName(String lastName) {
        Stream.of(new IfThenPair(lastName == null, "Last name cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.lastName = lastName;
    }

    /**
     * Returns the phone number of the client
     * @return A {@code String} representing the client's phone number
     */
    public String getPhoneNumber() {
        return phoneNumber;
    }

    /**
     * Sets the phone number of the client
     * @param phoneNumber The new phone number
     * @throws IllegalArgumentException if phoneNumber is null or is not a valid phone number
     *                                  (10 numbers starting with 0, optional prefix)
     */
    public void setPhoneNumber(String phoneNumber) {
        Stream.of(new IfThenPair(phoneNumber == null, "Phone number cannot be null!"),
                        new IfThenPair(phoneNumber!=null && !phoneNumber.matches("^(\\+4)?0[0-9]{9}$"),
                                "Phone number is not valid!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.phoneNumber = phoneNumber;
    }

    /**
     * Returns the email address of the client
     * @return A {@code String} representing the client's email address
     */
    public String getEmailAddress() {
        return emailAddress;
    }

    /**
     * Sets the email address of the client
     * @param emailAddress The new email address
     * @throws IllegalArgumentException if emailAddress is null or it does not contain @
     */
    public void setEmailAddress(String emailAddress) {
        Stream.of(new IfThenPair(emailAddress == null, "Email address cannot be null!"),
                        new IfThenPair(emailAddress!=null && !emailAddress.contains("@"),
                                "Email address is not valid!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.emailAddress = emailAddress;
    }

    /**
     * Returns the home address of the client
     * @return A {@code String} representing the client's home address
     */
    public String getHomeAddress() {
        return homeAddress;
    }

    /**
     * Sets the home address of the client
     * @param homeAddress The new home address
     * @throws IllegalArgumentException if homeAddress is null
     */
    public void setHomeAddress(String homeAddress) {
        Stream.of(new IfThenPair(homeAddress == null, "Home address cannot be null!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.homeAddress = homeAddress;
    }

    /**
     * Represents the client as a string
     * @return The {@code String} representation of the client.
     */
    @Override
    public String toString() {
        return "Client{" +
                "id=" + this.getId() +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", phoneNumber='" + phoneNumber + '\'' +
                ", emailAddress='" + emailAddress + '\'' +
                ", homeAddress='" + homeAddress + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client client = (Client) o;
        return firstName.equals(client.firstName) && lastName.equals(client.lastName)
                && phoneNumber.equals(client.phoneNumber) && emailAddress.equals(client.emailAddress)
                && homeAddress.equals(client.homeAddress);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, phoneNumber, emailAddress, homeAddress);
    }

    public static List<Client> readFromFile(String filePath, String delimiter) throws FileNotFoundException, IllegalArgumentException {
        List<Client> clients = new Vector<Client>();
        Scanner fileScanner = new Scanner(new File(filePath));
        fileScanner.useDelimiter(delimiter);
        Long id;
        String firstName, lastName, phoneNumber, emailAddress, homeAddress;

        while (fileScanner.hasNext()) {
            id = Optional.of(fileScanner).filter(Scanner::hasNextLong).map(Scanner::next).map(Long::valueOf).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a client must be a positive integer!"));
            firstName = fileScanner.next();
            lastName = fileScanner.next();
            phoneNumber = fileScanner.next();
            emailAddress = fileScanner.next();
            homeAddress = fileScanner.next();
            fileScanner.nextLine();
            clients.add(new Client(id, firstName, lastName, phoneNumber, emailAddress, homeAddress));
        }

        return clients;
    }
}
