package sdi.sensors.view;

import sdi.sensors.exceptions.ConnectionException;
import sdi.sensors.domain.Sensor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.sensors.service.SensorService;
import sdi.sensors.tcp.TcpClient;
import sdi.sensors.utils.dtos.SensorDto;
import sdi.sensors.utils.network.NetworkMessage;

import java.util.List;
import java.util.Optional;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;

@Component
public class Console {
    private final SensorService sensorService;
    private final ExecutorService executorService;
    private final Random generator;
    private final TcpClient tcpClient;

    private static final String SEND_SENSOR = "SEND_SENSOR";

    private Double generateRandomDouble(double inclusiveLowerBound, double exclusiveUpperBound) {
        return inclusiveLowerBound + (exclusiveUpperBound - inclusiveLowerBound) * generator.nextDouble();
    }

    @Autowired
    public Console(SensorService sensorService, ExecutorService executorService, TcpClient tcpClient) {
        this.sensorService = sensorService;
        this.executorService = executorService;
        this.tcpClient = tcpClient;
        generator = new Random();
        this.loadSensors();
    }

    private void loadSensors() {
        List<Sensor> sensors = null;
        try {
            sensors = sensorService.findAll().get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (ConnectionException e) {
            e.printStackTrace();
        }
        sensors.forEach(sensor -> {
            executorService.submit(() -> {
                while (true) {
                    var generated = generateRandomDouble(sensor.getLowerBound(), sensor.getUpperBound());
                    tcpClient.sendAndReceive(new NetworkMessage(SEND_SENSOR, new SensorDto(sensor.getId(), sensor.getName(), generated).encodeAsJson().toString()));
                    Thread.sleep(new Random().nextInt(10000));
//                  Thread.sleep(1000);
                }
            });
        });
    }

    private void addSensorCommand(Scanner scanner) {
        System.out.print("Sensor name: ");
        String sensorName = scanner.nextLine();

        try {
            if (!sensorService.findByName(sensorName).get().isEmpty()) {
                System.out.println("Invalid sensor name!");
                return;
            }
        } catch (ConnectionException | InterruptedException | ExecutionException e) {
            System.out.println("Invalid sensor name: " + e.getMessage());
            e.printStackTrace();
            return;
        }

        System.out.print("Sensor" + " ID: ");
        Integer sensorId = Optional.of(scanner).filter(Scanner::hasNextInt).map(Scanner::nextInt).filter(no -> no > 1023).orElseThrow(() -> new IllegalArgumentException("The ID of an sensor must be a greater than 1023!"));
        scanner.nextLine();

        System.out.print("Sensor" + " lower bound: ");
        Double sensorLowerBound = Optional.of(scanner).filter(Scanner::hasNextDouble).map(Scanner::nextDouble).orElseThrow(() -> new IllegalArgumentException("Invalid lower bound!"));
        scanner.nextLine();

        System.out.print("Sensor" + " upper bound: ");
        Double sensorUpperBound = Optional.of(scanner).filter(Scanner::hasNextDouble).map(Scanner::nextDouble).orElseThrow(() -> new IllegalArgumentException("Invalid upper bound!"));
        scanner.nextLine();

        var sensor = new Sensor(sensorId, sensorName, sensorLowerBound, sensorUpperBound);

        try {
            sensorService.save(sensor);
        } catch (ConnectionException e) {
            System.out.println("Error while saving: " + e.getMessage());
        }

        executorService.submit(() -> {
            while (true) {
                var generated = generateRandomDouble(sensor.getLowerBound(), sensor.getUpperBound());
                tcpClient.sendAndReceive(new NetworkMessage(SEND_SENSOR, new SensorDto(sensor.getId(), sensor.getName(), generated).encodeAsJson().toString()));
                Thread.sleep(new Random().nextInt(10000));
//                Thread.sleep(1000);
            }
        });
    }

    private void printMenu() {
        System.out.println("1 - add sensor");
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
                else if (command.equals("1")) {
                    addSensorCommand(scanner);
                }
            } catch (Exception error) {
                System.out.println("Error: " + error.getMessage() + "\n");
            }
        }
    }
}
