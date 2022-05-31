package sdi.client.view;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.client.service.DeviceService;
import sdi.web.dto.device.DeviceInsertDto;

import java.util.Optional;
import java.util.Scanner;

@Component
public class DeviceConsole extends ObjectConsole<DeviceInsertDto> {
    @Autowired
    public DeviceConsole(DeviceService service) {
        super(service);
    }

    @Override
    protected DeviceInsertDto readEntity(Scanner scanner) {
        System.out.print("Device type: ");
        String type = scanner.nextLine();
        System.out.print("Device brand: ");
        String brand = scanner.nextLine();
        System.out.print("Device model: ");
        String model = scanner.nextLine();
        System.out.print("Device client ID: ");
        Long clientID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
        scanner.nextLine();
        System.out.println();

        return new DeviceInsertDto(type, brand, model, clientID);
    }

    public void searchByClientId() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Client" + " ID: ");
        Long id = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a client must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        try {
            if (service instanceof DeviceService) {
                ((DeviceService) service).searchByClientId(id).forEach(System.out::println);
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }
}
