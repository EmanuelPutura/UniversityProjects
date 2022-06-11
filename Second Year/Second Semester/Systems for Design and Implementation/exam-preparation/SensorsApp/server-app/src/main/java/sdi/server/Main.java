package sdi.server;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import sdi.server.tcp.TcpServer;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("sdi.server.config");

        var tcpServer = context.getBean(TcpServer.class);
        tcpServer.startServer();
    }
}

