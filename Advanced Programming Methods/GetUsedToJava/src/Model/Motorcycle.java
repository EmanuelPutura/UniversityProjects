package Model;

public class Motorcycle implements IVehicle {
    private String color;
    private String model;

    public Motorcycle() {
        color = "";
        model = "";
    }

    public Motorcycle(String color, String model) {
        this.color = color;
        this.model = model;
    }

    public String getModel() {
        return model;
    }

    public String getColor() {
        return color;
    }

    public String toString() {
        return String.format("%s motorcycle, %s color", model, color);
    }

    public boolean equals(IVehicle vehicle) {
        return color.equals(vehicle.getColor()) && model.equals(vehicle.getModel());
    }
}
