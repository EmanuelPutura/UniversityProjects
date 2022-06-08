package sdi.sensors;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import sdi.sensors.view.Console;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("sdi.sensors.config");
        var console = context.getBean(Console.class);
        console.run();
    }
}
