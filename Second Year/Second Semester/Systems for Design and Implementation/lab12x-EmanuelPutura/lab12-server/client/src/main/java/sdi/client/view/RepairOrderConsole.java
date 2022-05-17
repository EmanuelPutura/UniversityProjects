package sdi.client.view;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.client.service.RepairOrderService;
import sdi.core.model.exceptions.ValidatorException;
import sdi.web.dto.orders.RepairOrderDto;

import java.util.Optional;
import java.util.Scanner;

@Component
public class RepairOrderConsole extends ObjectConsole<RepairOrderDto> {
    @Autowired
    public RepairOrderConsole(RepairOrderService service) {
        super(service);
    }

    @Override
    protected RepairOrderDto readEntity(Scanner scanner) {
        System.out.print("Device ID: ");
        Long deviceID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a Device must be a positive integer!"));
        System.out.print("Technician ID: ");
        Long technicianID = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a Technician must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        return new RepairOrderDto(technicianID, deviceID);
    }

    @Override
    public void deleteEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Technician" + " ID: ");
            Long technicianId = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of an entity must be a positive integer!"));
            scanner.nextLine();  // extract the new line remained from the nextLong() function call

            System.out.print("Device" + " ID: ");
            Long deviceId = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of an entity must be a positive integer!"));
            scanner.nextLine();  // extract the new line remained from the nextLong() function call

            if (service instanceof RepairOrderService)
                ((RepairOrderService) service).deleteByIds(technicianId, deviceId);
        } catch (ValidatorException e) {
            System.out.println("Error: " + e.toString());
        }
    }

    public void findAllTechnicianWorkingOnDevice() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Device" + " ID: ");
        Long id = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of a device must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        try {
            if (service instanceof RepairOrderService) {
                ((RepairOrderService) service).findAllTechnicianWorkingOnDevice(id).forEach(System.out::println);
            }
        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }
}
