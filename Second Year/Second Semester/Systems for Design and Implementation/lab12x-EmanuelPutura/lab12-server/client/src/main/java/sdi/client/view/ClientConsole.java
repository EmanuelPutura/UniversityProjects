package sdi.client.view;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.client.service.ClientService;
import sdi.web.dto.client.ClientDto;

import java.util.Scanner;

@Component
public class ClientConsole extends ObjectConsole<ClientDto> {
    @Autowired
    public ClientConsole(ClientService service) {
        super(service);
    }

    @Override
    protected ClientDto readEntity(Scanner scanner) {
        System.out.print("Client first name: ");
        String firstName = scanner.nextLine();
        System.out.print("Client last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Client email address: ");
        String emailAddress = scanner.nextLine();
        System.out.println();

        return new ClientDto(firstName, lastName, emailAddress);
    }
}
