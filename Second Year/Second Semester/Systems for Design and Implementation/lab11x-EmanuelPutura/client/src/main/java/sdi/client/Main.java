package sdi.client;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import sdi.client.view.Console;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("sdi.client.config");
        var console = context.getBean(Console.class);
        console.run();
    }
}
