package sdi.client.view;

import org.javatuples.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

@Component
public class Console {
    private static final Integer CLIENT_CODE = 1;
    private static final Integer DEVICE_CODE = 2;
    private static final Integer TECHNICIAN_CODE = 3;
    private static final Integer REPAIR_ORDER_CODE = 4;
    private static final Integer OTHER_OPERATIONS_CODE = 5;

    private static final Integer ADD_CODE = 1;
    private static final Integer UPDATE_CODE = 2;
    private static final Integer DELETE_CODE = 3;
    private static final Integer PRINT_CODE = 4;

    private static final Integer EXIT_CODE = 0;

    private final Map<Integer, Map<Integer, Runnable>> consolesMap;

    private final DeviceConsole deviceConsole;
    private final RepairOrderConsole repairOrderConsole;

    @Autowired
    public Console(ClientConsole clientConsole, DeviceConsole deviceConsole, TechnicianConsole technicianConsole, RepairOrderConsole repairOrderConsole) {
        this.deviceConsole = deviceConsole;
        this.repairOrderConsole = repairOrderConsole;

        consolesMap = new HashMap<>() {{
            put(CLIENT_CODE, Console.createEntityConsoleMap(clientConsole));
            put(DEVICE_CODE, Console.createEntityConsoleMap(deviceConsole));
            put(TECHNICIAN_CODE, Console.createEntityConsoleMap(technicianConsole));
            put(REPAIR_ORDER_CODE, Console.createEntityConsoleMap(repairOrderConsole));
        }};
    }

    private static <T extends GenericConsole> Map<Integer, Runnable> createEntityConsoleMap(T entityConsole) {
        return new HashMap<>(){{
            put(ADD_CODE, entityConsole::addEntity);
            put(DELETE_CODE, entityConsole::deleteEntity);
            put(UPDATE_CODE, entityConsole::updateEntity);
            put(PRINT_CODE, entityConsole::printAllEntities);
        }};
    }

    private void printMenu() {
        System.out.println("\n" + IntStream.range(0, 100).mapToObj(el -> "*").collect(Collectors.joining()));
        System.out.println("For common commands, please use the entity number concatenated with the feature number.");
        System.out.println("For commands implying multiple entities, use the specific command code.");
        System.out.println("(e.g., 11 - add a client)");
        System.out.printf(CLIENT_CODE + " - client:\n\t%d - add a client\n\t%d - update a client\n\t%d - delete a client\n\t%d - print all clients%n", ADD_CODE, UPDATE_CODE, DELETE_CODE, PRINT_CODE);
        System.out.printf(DEVICE_CODE + " - device:\n\t1 - add a device\n\t2 - update a device\n\t3 - delete a device\n\t4 - print all devices%n", ADD_CODE, UPDATE_CODE, DELETE_CODE, PRINT_CODE);
        System.out.printf(TECHNICIAN_CODE + " - technician:\n\t1 - add a technician\n\t2 - update a technician\n\t3 - delete a technician\n\t4 - print all technicians%n", ADD_CODE, UPDATE_CODE, DELETE_CODE, PRINT_CODE);
        System.out.printf(REPAIR_ORDER_CODE + " - repair order:\n\t1 - add a repair order\n\t2 - update a repair order\n\t3 - delete a repair order\n\t4 - print all repair orders%n", ADD_CODE, UPDATE_CODE, DELETE_CODE, PRINT_CODE);
        System.out.print(OTHER_OPERATIONS_CODE + " - other operations:\n\t1 - get all devices associated with a certain client\n\t");
        System.out.println("2 - get all technicians that are working on repair orders given for a certain device");

        System.out.println(IntStream.range(0, 100).mapToObj(el -> "*").collect(Collectors.joining()) + "\n");
    }

    private Pair<Integer, Integer> getCommandOptions(String command) {
        if (!command.matches("[0-9]{2}")) {
            return null;
        }

        var intCommand = Integer.parseInt(command);
        return new Pair<>(intCommand / 10, intCommand % 10);
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            try {
                printMenu();
                System.out.print(">> ");
                String command = scanner.nextLine();

                if (command.equals("0")) {
                    System.exit(0);
                }

                var cmdOptions = getCommandOptions(command);
                if (cmdOptions == null) {
                    continue;
                }

                var firstCmdOption = cmdOptions.getValue0();
                var secondCmdOption = cmdOptions.getValue1();

                if (firstCmdOption == 5 && secondCmdOption == 1) {
                    deviceConsole.searchByClientId();
                }
                else if (firstCmdOption == 5 && secondCmdOption == 2) {
                    repairOrderConsole.findAllTechnicianWorkingOnDevice();
                }
                else {
                    consolesMap.get(firstCmdOption).get(secondCmdOption).run();
                }
            } catch (Exception error) {
                System.out.println("Error: " + error.toString() + "\n");
            }
        }
    }
}
