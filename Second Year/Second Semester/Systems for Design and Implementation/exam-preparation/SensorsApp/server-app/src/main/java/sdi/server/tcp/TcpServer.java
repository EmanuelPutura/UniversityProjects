package sdi.server.tcp;

import org.springframework.stereotype.Component;
import sdi.server.utils.network.NetworkConnection;
import sdi.server.utils.network.NetworkMessage;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.function.UnaryOperator;

@Component
public class TcpServer {
    private final ExecutorService executorService;
    private final Map<String, UnaryOperator<NetworkMessage>> methodHandlers;

    public TcpServer(ExecutorService executorService) {
        this.executorService = executorService;
        this.methodHandlers = new HashMap<>();
    }

    public void addHandler(String methodName, UnaryOperator<NetworkMessage> handler) {
        methodHandlers.put(methodName, handler);
    }

    public void startServer() {
        int port = NetworkConnection.SERVER_PORT;
        try (var serverSocket = new ServerSocket(port)) {
            System.out.println("server started; waiting for clients...");
            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("client connected");
                executorService.submit(new ClientHandler(clientSocket));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    private class ClientHandler implements Runnable {
        private final Socket socket;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try (var is = socket.getInputStream();
                 var os = socket.getOutputStream()) {

                //read the request (of type Message) from client
                NetworkMessage request = new NetworkMessage();
                request.readFrom(is);
//                System.out.println("received request: " + request);

                // compute response (of type Message)
                NetworkMessage response = methodHandlers.get(request.getHeader()).apply(request);
//                System.out.println("computed response: " + response);

                //send response (of type Message) to client
                response.writeTo(os);
//                System.out.println("response sent to client");
                try {
                    Thread.sleep(new Random().nextInt(10000));
//                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    System.out.println(e.getMessage());
                }
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}


