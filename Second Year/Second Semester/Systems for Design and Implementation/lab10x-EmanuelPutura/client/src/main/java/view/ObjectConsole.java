package view;

import domain.BaseEntity;
import domain.exceptions.ConnectionException;
import domain.exceptions.ValidatorException;
import org.springframework.stereotype.Component;
import service.GenericService;

import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

@Component
public abstract class ObjectConsole<T extends BaseEntity<Long>> implements GenericConsole {
    protected GenericService<Long, T> service;

    public ObjectConsole(GenericService<Long, T> service) {
        this.service = service;
    }

    protected abstract T readEntity(Scanner scanner);

    protected Long readId(Scanner scanner) {
        System.out.print("Entity" + " ID: ");
        Long id = Optional.of(scanner).filter(Scanner::hasNextLong).map(Scanner::nextLong).filter(no -> no > 0).orElseThrow(() -> new IllegalArgumentException("The ID of an entity must be a positive integer!"));
        scanner.nextLine();  // extract the new line remained from the nextLong() function call

        return id;
    }

    public void addEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            service.save(readEntity(scanner));
        } catch (ConnectionException | ValidatorException e) {
            System.out.println(e.toString());
        }
    }

    public void updateEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            service.update(readEntity(scanner));
        } catch (ConnectionException | ValidatorException e) {
            System.out.println(e.toString());
        }
    }

    public void deleteEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            service.deleteById(readId(scanner));
        } catch (ConnectionException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public void printAllEntities() {
        try {
            var entities = service.findAll().get();

            if (entities.size() == 0) {
                System.out.println("There are currently no entities of the selected type in the database!");
                return;
            }

            System.out.println("The already added entities of the selected type are:");
            entities.forEach(System.out::println);
        } catch (InterruptedException | ExecutionException | ConnectionException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
