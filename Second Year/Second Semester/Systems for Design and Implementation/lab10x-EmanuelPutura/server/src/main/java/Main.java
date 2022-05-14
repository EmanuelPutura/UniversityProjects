import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import tcp.TcpServer;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("config");

        var tcpServer = context.getBean(TcpServer.class);
        tcpServer.startServer();
    }
}
