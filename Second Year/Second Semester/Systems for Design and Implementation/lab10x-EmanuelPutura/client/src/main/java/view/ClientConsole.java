package view;

import domain.entities.Client;
import org.springframework.stereotype.Component;
import service.ClientService;

import java.util.Scanner;

@Component
public class ClientConsole extends ObjectConsole<Client> {
    public ClientConsole(ClientService service) {
        super(service);
    }

    @Override
    protected Client readEntity(Scanner scanner) {
        Long id = readId(scanner);

        System.out.print("Client first name: ");
        String firstName = scanner.nextLine();
        System.out.print("Client last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Client phone number: ");
        String phoneNumber = scanner.nextLine();
        System.out.print("Client email address: ");
        String emailAddress = scanner.nextLine();
        System.out.print("Client home address: ");
        String homeAddress = scanner.nextLine();
        System.out.println();

        return new Client(id, firstName, lastName, phoneNumber, emailAddress, homeAddress);
    }
}
