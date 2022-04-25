package Model;

public class Bicycle implements IVehicle {
    private String color;
    private String model;

    public Bicycle() {
        color = "";
        model = "";
    }

    public Bicycle(String color, String model) {
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
        return String.format("%s bycicle, %s color", model, color);
    }

    public boolean equals(IVehicle vehicle) {
        return color.equals(vehicle.getColor()) && model.equals(vehicle.getModel());
    }
}
