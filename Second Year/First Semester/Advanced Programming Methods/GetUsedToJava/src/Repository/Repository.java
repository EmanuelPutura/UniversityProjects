package Repository;

import Model.IVehicle;

public class Repository implements IRepository {
    private IVehicle[] vehicles;
    private int capacity, length;

    public Repository() {
        capacity = 10;
        length = 0;
        vehicles = new IVehicle[capacity];
    }

    public void add(IVehicle vehicle) throws RepositoryException {
        for (IVehicle v : vehicles) {
            if (v != null && v.equals(vehicle))
                throw new RepositoryException(String.format("Vehicle '%s' was already added to the repository.", vehicle.toString()));
        }

        if (length == capacity)
            resize();

        vehicles[length] = vehicle;
        length++;
    }

    public void remove(IVehicle vehicle) throws RepositoryException {
        int index = -1;
        for (int i = 0; i < length; ++i) {
            if (vehicles[i].equals(vehicle)) {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw new RepositoryException(String.format("Vehicle '%s' was not found in the repository.", vehicle.toString()));
        else {
            for (int i = index; i < length; ++i)
                vehicles[i] = vehicles[i + 1];
            length--;
        }
    }

    public int size() {
        return length;
    }

    public IVehicle[] data() {
        return vehicles;
    }

    private void resize() {
        IVehicle[] new_array = new IVehicle[capacity * 2];
        for (int i = 0; i < capacity; ++i)
            new_array[i] = vehicles[i];
        vehicles = new_array;
        capacity *= 2;
    }
}