package domain.entities;

import domain.BaseEntity;
import utils.IfThenPair;

import java.util.Objects;
import java.util.stream.Stream;

public class Technician extends BaseEntity<Long> {
    private String firstName;
    private String lastName;
    private Long salary;
    private String phoneNumber;
    private String emailAddress;
    private String homeAddress;
    private Long employeeNumber;

    /**
     * Creates a new Technician object
     *
     * @param ID             the ID of the technician, cannot be null
     * @param firstName      the first name, cannot be null or empty
     * @param lastName       the last name, cannot be null or empty
     * @param salary         the salary, cannot be null, cannot be negative
     * @param phoneNumber    the phone number, cannot be null, has to be valid
     * @param emailAddress   the email address, cannot be null, has to be valid
     * @param homeAddress    the home address, cannot be null or empty
     * @param employeeNumber the number of employees, cannot be null, cannot be negative
     */
    public Technician(Long ID, String firstName, String lastName, Long salary, String phoneNumber, String emailAddress, String homeAddress, Long employeeNumber) {
        this.setId(ID);
        this.firstName = firstName;
        this.lastName = lastName;
        this.salary = salary;
        this.phoneNumber = phoneNumber;
        this.emailAddress = emailAddress;
        this.homeAddress = homeAddress;
        this.employeeNumber = employeeNumber;
    }

    @Override
    public String toString() {
        return "Technician{" +
                "ID=" + this.getId() +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", salary=" + salary +
                ", phoneNumber='" + phoneNumber + '\'' +
                ", emailAddress='" + emailAddress + '\'' +
                ", streetAddress='" + homeAddress + '\'' +
                ", employeeNumber=" + employeeNumber +
                '}';
    }

    /**
     * Gets the Technician's first name.
     *
     * @return a {@code String} - firstName
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Sets the Technician's first name to the given value.
     *
     * @param firstName new first name
     * @throws IllegalArgumentException if firstName is null or empty
     */
    public void setFirstName(String firstName) {
        Stream.of(new IfThenPair(firstName==null, "First name cannot be null!"),
                        new IfThenPair(firstName!=null && firstName.isEmpty(), "First name cannot be empty!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.firstName = firstName;
    }

    /**
     * Gets the Technician's last name.
     *
     * @return a {@code String} - lastName
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Sets the Technician's last name to the given value.
     *
     * @param lastName new last name
     * @throws IllegalArgumentException if lastName is null or empty
     */
    public void setLastName(String lastName) {
        Stream.of(new IfThenPair(lastName==null, "Last name cannot be null!"),
                        new IfThenPair(lastName!=null && lastName.isEmpty(), "Last name cannot be empty!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.lastName = lastName;
    }

    /**
     * Gets the Technician's salary.
     *
     * @return a {@code Long} - salary
     */
    public Long getSalary() {
        return salary;
    }

    /**
     * Sets the Technician's salary to the given value.
     *
     * @param salary new salary
     * @throws IllegalArgumentException if salary is null or negative
     */
    public void setSalary(Long salary) {
        Stream.of(new IfThenPair(salary==null, "Salary cannot be null!"),
                        new IfThenPair(salary!=null && salary < 0, "Salary cannot be negative!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.salary = salary;
    }

    /**
     * Gets the Technician's phone number.
     *
     * @return a {@code String} - phoneNumber
     */
    public String getPhoneNumber() {
        return phoneNumber;
    }

    /**
     * Sets the Technician's phone number to the given value.
     *
     * @param phoneNumber new phone number
     * @throws IllegalArgumentException if phoneNumber is null or not valid (10 digits starting with 0)
     */
    public void setPhoneNumber(String phoneNumber) {
        Stream.of(new IfThenPair(phoneNumber==null, "Phone number cannot be null!"),
                        new IfThenPair(phoneNumber!=null && !phoneNumber.matches("^(\\+4)?0[0-9]{9}$"),
                                "Phone number is not valid!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.phoneNumber = phoneNumber;
    }

    /**
     * Gets the Technician's email address.
     *
     * @return a {@code String} - emailAddress
     */
    public String getEmailAddress() {
        return emailAddress;
    }

    /**
     * Sets the Technician's email address to the given value.
     *
     * @param emailAddress new email address.
     * @throws IllegalArgumentException if emailAddress is null or invalid (does not contain @)
     */
    public void setEmailAddress(String emailAddress) {
        Stream.of(new IfThenPair(emailAddress==null, "Email address cannot be null!"),
                        new IfThenPair(emailAddress!=null && !emailAddress.contains("@"),
                                "Email address is not valid!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.emailAddress = emailAddress;
    }

    /**
     * Gets the Technician's street address
     *
     * @return a {@code String} - streetAddress
     */
    public String getHomeAddress() {
        return homeAddress;
    }

    /**
     * Sets the Technician's street address to the given value.
     *
     * @param homeAddress new street address
     * @throws IllegalArgumentException if homeAddress is null or empty
     */
    public void setHomeAddress(String homeAddress) {
        Stream.of(new IfThenPair(homeAddress==null, "Home address cannot be null!"),
                        new IfThenPair(homeAddress!=null && homeAddress.isEmpty(), "Home address cannot be empty!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.homeAddress = homeAddress;
    }

    /**
     * Gets the Technician's employee number.
     *
     * @return a {@code Long} - employeeNumber
     */
    public Long getEmployeeNumber() {
        return employeeNumber;
    }

    /**
     * Sets the Technician's employee number to the given value.
     *
     * @param employeeNumber new employeeNumber
     * @throws IllegalArgumentException if employeeNumber is null or negative
     */
    public void setEmployeeNumber(Long employeeNumber) {
        Stream.of(new IfThenPair(employeeNumber==null, "Employee number cannot be null!"),
                        new IfThenPair(employeeNumber!=null && employeeNumber < 0,
                                "Employee number cannot be negative!"))
                .filter(IfThenPair::getIfCondition)
                .forEach(elem -> {throw new IllegalArgumentException(elem.getThenError());});
        this.employeeNumber = employeeNumber;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Technician that = (Technician) o;
        return Objects.equals(salary, that.salary) && Objects.equals(employeeNumber, that.employeeNumber) && Objects.equals(firstName, that.firstName) && Objects.equals(lastName, that.lastName) && Objects.equals(phoneNumber, that.phoneNumber) && Objects.equals(emailAddress, that.emailAddress) && Objects.equals(homeAddress, that.homeAddress);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName, salary, phoneNumber, emailAddress, homeAddress, employeeNumber);
    }

}