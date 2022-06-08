package sdi.server;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import sdi.server.view.Console;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("config");

        Console console = context.getBean(Console.class);
        console.run();
    }
}

