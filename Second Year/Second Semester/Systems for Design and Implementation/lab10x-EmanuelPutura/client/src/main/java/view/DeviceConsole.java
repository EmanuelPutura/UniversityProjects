package view;

import domain.entities.Device;
import domain.exceptions.ConnectionException;
import org.springframework.stereotype.Component;
import service.DeviceService;

import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

@Component
public class DeviceConsole extends ObjectConsole<Device> {
    public DeviceConsole(DeviceService service) {
        super(service);
    }

    @Override
    protected Device readEntity(Scanner scanner) {
        Long id = readId(scanner);

        System.out.print("Device type: ");
        String type = scanner.nextLine();
        System.out.print("Device brand: ");
        String brand = scanner.nextLine();
        System.out.print("Device model: ");
        String model = scanner.nextLine();
        System.out.print("Device client ID: ");
        Long clientID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
        scanner.nextLine();

        return new Device(id, type, brand, model, clientID);
    }

    public void searchByClientId() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Client" + " ID: ");
        Long id = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a client must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        try {
            if (service instanceof DeviceService) {
                ((DeviceService) service).searchByClientId(id).get().forEach(System.out::println);
            }
        } catch (ConnectionException | InterruptedException | ExecutionException e) {
            System.out.println(e.toString());
        }
    }
}
