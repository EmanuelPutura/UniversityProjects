package view;

import domain.entities.Technician;
import org.springframework.stereotype.Component;
import service.TechnicianService;

import java.util.Optional;
import java.util.Scanner;

@Component
public class TechnicianConsole extends ObjectConsole<Technician> {
    public TechnicianConsole(TechnicianService service) {
        super(service);
    }

    @Override
    protected Technician readEntity(Scanner scanner) {
        Long id = readId(scanner);

        System.out.print("Technician first name: ");
        String firstName = scanner.nextLine();
        System.out.print("Technician last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Technician salary: ");
        Long salary = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The salary of the technician must be a positive integer"));
        scanner.nextLine();
        System.out.print("Technician phone number: ");
        String phoneNumber = scanner.nextLine();
        System.out.print("Technician email address: ");
        String emailAddress = scanner.nextLine();
        System.out.print("Technician home address: ");
        String homeAddress = scanner.nextLine();
        System.out.print("Technician employee number: ");
        Long employeeNumber = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The employee number of the technician must be a positive integer"));
        System.out.println();

        return new Technician(id, firstName, lastName, salary, phoneNumber, emailAddress, homeAddress, employeeNumber);
    }
}
