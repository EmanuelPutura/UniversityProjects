package view;

import domain.BaseEntity;
import domain.entities.RepairOrder;
import domain.exceptions.ConnectionException;
import org.springframework.stereotype.Component;
import service.DeviceService;
import service.GenericService;
import service.RepairOrderService;

import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

@Component
public class RepairOrderConsole extends ObjectConsole<RepairOrder> {
    public RepairOrderConsole(RepairOrderService service) {
        super(service);
    }

    @Override
    protected RepairOrder readEntity(Scanner scanner) {
        Long id = readId(scanner);

        System.out.print("Device ID: ");
        Long deviceID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a Device must be a positive integer!"));
        System.out.print("Technician ID: ");
        Long technicianID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a Technician must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call
        System.out.print("Date brought: ");
        String dateBrought = scanner.nextLine();
        System.out.print("Date expected: ");
        String dateExpected = scanner.nextLine();
        System.out.print("Cost: ");
        Float cost = Optional.of(scanner).filter(Scanner::hasNextFloat).map(Scanner::nextFloat).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The cost of a RepairOrder must be positive!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        return new RepairOrder(id, deviceID, technicianID, dateBrought, dateExpected, cost);
    }

    public void findAllTechnicianWorkingOnDevice() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Device" + " ID: ");
        Long id = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        try {
            if (service instanceof RepairOrderService) {
                ((RepairOrderService) service).findAllTechnicianWorkingOnDevice(id).get().forEach(System.out::println);
            }
        } catch (ConnectionException | InterruptedException | ExecutionException e) {
            System.out.println(e.toString());
        }
    }
}
