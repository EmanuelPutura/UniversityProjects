package View.Console;

import java.util.*;

public class TextMenu {
    private Map<String, Command> commands;

    public TextMenu() {
        commands = new HashMap<String, Command>();
    }

    public void addCommand(Command command) {
        commands.put(command.getKey(), command);
    }

    public void printMenu() {
        List<Map.Entry<String, Command>> list = new ArrayList<>(commands.entrySet());
        list.sort((e1, e2) -> Integer.parseInt(e1.getValue().getKey()) - Integer.parseInt(e2.getValue().getKey()));
        for (Map.Entry<String, Command> stringCommandEntry : list) {
            String line = String.format("%4s : %s", stringCommandEntry.getValue().getKey(), stringCommandEntry.getValue().getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while(true) {
            printMenu();
            System.out.print("Input the option: ");
            String key = scanner.nextLine();
            Command command = commands.get(key);
            if (command == null) {
                System.out.println("Invalid option!");
                continue;
            }
            command.execute();
        }
    }
}
