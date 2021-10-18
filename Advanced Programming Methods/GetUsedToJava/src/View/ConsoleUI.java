package View;

import Controller.Controller;
import Controller.ControllerException;
import Model.IVehicle;
import java.util.Scanner;

public class ConsoleUI {
    private Controller controller;

    public ConsoleUI(Controller controller) {
        this.controller = controller;
    }

    public void run() {
        controller.init();
        while (true) {
            printMenu();
            Scanner scanner = new Scanner(System.in);
            System.out.print("command >> ");
            String input = scanner.nextLine();

            switch (input) {
                case "add":
                    add();
                    break;
                case "remove":
                    remove();
                    break;
                case "display":
                    display();
                    break;
                case "filter":
                    filter();
                    break;
                case "exit":
                    return;
                default:
                    System.out.println("Invalid command.");
            }
        }
    }

    private void printMenu() {
        System.out.println("--------------------------- Assignment 1 ---------------------------");
        System.out.println("add - add a vehicle to the repository");
        System.out.println("remove - remove a vehicle from the repository");
        System.out.println("display - display all vehicles");
        System.out.println("filter - filter vehicles by color");
        System.out.println("exit - exit the application");
        System.out.println("--------------------------------------------------------------------");
        System.out.println();
    }

    private void printVehicles(IVehicle[] vehicles) {
        for (IVehicle v : vehicles) {
            if (v == null) break;
            System.out.println(v);
        }
    }

    private void add() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("type [car | bicycle | motorcycle] >> ");

        String type = scanner.nextLine();
        Vehicles vehicle_type;

        switch (type) {
            case "car":
                vehicle_type = Vehicles.CAR;
                break;
            case "bicycle":
                vehicle_type = Vehicles.BICYCLE;
                break;
            case "motorcycle":
                vehicle_type = Vehicles.MOTORCYCLE;
                break;
            default:
                System.out.println("Invalid vehicle type.");
                return;
        }

        System.out.print("color >> ");
        String color = scanner.nextLine();
        System.out.print("model >> ");
        String model = scanner.nextLine();

        try {
            controller.add(vehicle_type, color, model);
        } catch (ControllerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void remove() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("type [car | bicycle | motorcycle] >> ");

        String type = scanner.nextLine();
        Vehicles vehicle_type;

        switch (type) {
            case "car":
                vehicle_type = Vehicles.CAR;
                break;
            case "bicycle":
                vehicle_type = Vehicles.BICYCLE;
                break;
            case "motorcycle":
                vehicle_type = Vehicles.MOTORCYCLE;
                break;
            default:
                System.out.println("Invalid vehicle type.");
                return;
        }

        System.out.print("color >> ");
        String color = scanner.nextLine();
        System.out.print("model >> ");
        String model = scanner.nextLine();

        try {
            controller.remove(vehicle_type, color, model);
        } catch (ControllerException e) {
            System.out.println(e.getMessage());
        }
    }

    private void display() {
        printVehicles(controller.vehicles());
    }

    private void filter() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("color >> ");
        String color = scanner.nextLine();
        printVehicles(controller.getVehiclesWithCertainColor(color));
    }
}
