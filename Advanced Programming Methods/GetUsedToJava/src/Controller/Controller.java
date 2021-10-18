package Controller;

import Model.Bicycle;
import Model.Car;
import Model.IVehicle;
import Model.Motorcycle;
import Repository.IRepository;
import Repository.RepositoryException;
import View.Vehicles;

public class Controller {
    private IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public IVehicle[] vehicles() {
        return repository.data();
    }

    public IVehicle[] getVehiclesWithCertainColor(String color) {
        IVehicle[] data = repository.data(), vehicles = new IVehicle[repository.size()];
        int index = 0;
        for (IVehicle vehicle : data) {
            if (vehicle == null)
                break;
            if (vehicle.getColor().equals(color)) {
                vehicles[index] = vehicle;
                index++;
            }
        }

        return vehicles;
    }

    public void add(Vehicles type, String color, String model) throws ControllerException {
        IVehicle vehicle = getVehicleFromData(type, color, model);

        try {
            repository.add(vehicle);
        } catch (RepositoryException e) {
            throw new ControllerException(e.getMessage());
        }
    }

    public void remove(Vehicles type, String color, String model) throws ControllerException {
        IVehicle vehicle = getVehicleFromData(type, color, model);

        try {
            repository.remove(vehicle);
        } catch (RepositoryException e) {
            throw new ControllerException(e.getMessage());
        }
    }

    public void init() {
        try {
            add(Vehicles.CAR, "green", "BMW");
            add(Vehicles.BICYCLE, "red", "Schwinn");
            add(Vehicles.BICYCLE, "blue", "Cannondale");
            add(Vehicles.CAR, "red", "VW");
            add(Vehicles.CAR, "black", "Ford");
            add(Vehicles.MOTORCYCLE, "red", "Harley-Davidson");
        } catch (ControllerException e) {
            return;
        }
    }

    private IVehicle getVehicleFromData(Vehicles type, String color, String model) throws ControllerException {
        switch (type) {
            case CAR:
                return new Car(color, model);
            case BICYCLE:
                return new Bicycle(color, model);
            case MOTORCYCLE:
                return new Motorcycle(color, model);
            default:
                throw new ControllerException("Invalid vehicle type.");
        }
    }
}
