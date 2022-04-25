package Model;

public interface IVehicle {
    String getColor();
    String getModel();
    String toString();

    boolean equals(IVehicle vehicle);
}
