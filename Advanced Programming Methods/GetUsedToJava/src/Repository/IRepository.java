package Repository;

import Model.IVehicle;

public interface IRepository {
    void add(IVehicle vehicle) throws RepositoryException;
    void remove(IVehicle vehicle) throws RepositoryException;

    int size();
    IVehicle[] data();
}
