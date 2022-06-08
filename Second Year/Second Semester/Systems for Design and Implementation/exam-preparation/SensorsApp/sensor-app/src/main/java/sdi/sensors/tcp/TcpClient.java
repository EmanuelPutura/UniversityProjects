package sdi.sensors.tcp;

import sdi.sensors.exceptions.ConnectionException;
import org.springframework.stereotype.Component;
import sdi.sensors.utils.network.NetworkConnection;
import sdi.sensors.utils.network.NetworkMessage;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

@Component
public class TcpClient {
    public NetworkMessage sendAndReceive(NetworkMessage request) throws ConnectionException {
        try (var socket = new Socket(NetworkConnection.SERVER_ADDRESS, NetworkConnection.SERVER_PORT);
             var is = socket.getInputStream();
             var os = socket.getOutputStream()) {

            System.out.println("sending request: " + request.getHeader());
            request.writeTo(os);
            System.out.println("request sent");

            NetworkMessage response = new NetworkMessage();
            response.readFrom(is);
            System.out.println("received response: " + response.getHeader());

            return response;
        } catch (UnknownHostException e) {
            e.printStackTrace();
            throw new ConnectionException("Tried to connect to unknown host!");
        } catch (IOException e) {
            e.printStackTrace();
            throw new ConnectionException("I/O error occurred while creating the socket!");
        }

    }
}
