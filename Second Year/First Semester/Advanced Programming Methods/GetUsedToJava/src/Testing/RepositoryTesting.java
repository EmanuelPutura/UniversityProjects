package Testing;

import Model.Bicycle;
import Model.Car;
import Model.IVehicle;
import Model.Motorcycle;
import Repository.IRepository;
import Repository.Repository;
import Repository.RepositoryException;

public class RepositoryTesting {
    public static void test() {
        IRepository repository = new Repository();
        assert repository.size() == 0;

        IVehicle c1 = new Car("red", "BMW");
        try {
            repository.add(c1);
            assert repository.size() == 1;
            assert repository.data()[0].getModel().equals("BMW");
        } catch (RepositoryException e) {
            assert false;
        }

        try {
            repository.add(c1);
            assert false;
        }
        catch (RepositoryException e) {
            assert true;
        }

        IVehicle b1 = new Bicycle("green", "Cool bicycle model");
        try {
            repository.add(b1);
            assert repository.size() == 2;
            assert repository.data()[1].getColor().equals("green");
        } catch (RepositoryException e) {
            assert false;
        }

        IVehicle m1 = new Motorcycle("red", "Cool motorcycle model");
        try {
            repository.add(m1);
            assert repository.size() == 3;
            assert repository.data()[2].getColor().equals("red");
        } catch (RepositoryException e) {
            assert false;
        }

        try {
            repository.remove(b1);
            assert repository.size() == 2;
            assert repository.data()[1].getModel().equals("Cool motorcycle model");
        } catch (RepositoryException e) {
            assert false;
        }
    }
}
