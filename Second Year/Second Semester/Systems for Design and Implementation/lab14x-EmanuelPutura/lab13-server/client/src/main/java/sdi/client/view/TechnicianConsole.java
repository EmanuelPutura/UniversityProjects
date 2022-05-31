package sdi.client.view;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.client.service.TechnicianService;
import sdi.web.dto.technician.TechnicianDto;

import java.util.Optional;
import java.util.Scanner;

@Component
public class TechnicianConsole extends ObjectConsole<TechnicianDto> {
    @Autowired
    public TechnicianConsole(TechnicianService service) {
        super(service);
    }

    @Override
    protected TechnicianDto readEntity(Scanner scanner) {
        System.out.print("Technician first name: ");
        String firstName = scanner.nextLine();
        System.out.print("Technician last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Technician salary: ");
        Long salary = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The salary of the technician must be a positive integer"));
        scanner.nextLine();
        System.out.println();

        return new TechnicianDto(firstName, lastName, salary);
    }
}
