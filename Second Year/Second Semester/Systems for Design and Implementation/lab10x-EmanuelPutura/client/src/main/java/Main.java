import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import view.Console;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("config");
        var console = context.getBean(Console.class);
        console.run();
    }
}