package sdi.client.view;

import sdi.client.service.CrudService;
import sdi.core.model.exceptions.ValidatorException;
import sdi.web.dto.BaseDto;

import java.util.Optional;
import java.util.Scanner;

public abstract class ObjectConsole<T extends BaseDto> implements GenericConsole {
    protected CrudService<T> service;

    public ObjectConsole(CrudService<T> service) {
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
        } catch (ValidatorException e) {
            System.out.println(e.toString());
        }
    }

    public void updateEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            var id = readId(scanner);
            var entity = readEntity(scanner);
            entity.setId(id);

            service.update(entity);
        } catch (ValidatorException e) {
            System.out.println(e.toString());
        }
    }

    public void deleteEntity() {
        Scanner scanner = new Scanner(System.in);
        try {
            service.deleteById(readId(scanner));
        } catch (ValidatorException e) {
            System.out.println("Error: " + e.toString());
        }
    }

    public void printAllEntities() {
        try {
            var entities = service.getAll();

            if (entities.size() == 0) {
                System.out.println("There are currently no entities of the selected type in the database!");
                return;
            }

            System.out.println("The already added entities of the selected type are:");
            entities.forEach(System.out::println);
        } catch (Exception e) {
            System.out.println("Error: " + e.toString());
        }
    }
}
