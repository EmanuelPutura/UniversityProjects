package service;

import domain.entities.Client;
import domain.exceptions.ConnectionException;
import domain.validators.ClientValidator;
import org.json.JSONArray;
import org.springframework.stereotype.Service;
import tcp.TcpClient;
import utils.encoders.ClientJsonEncoder;
import utils.network.NetworkMessage;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class ClientServiceImpl implements ClientService {
    private final TcpClient tcpClient;
    private final ExecutorService executorService;
    private final ClientJsonEncoder clientJsonEncoder;
    private final ClientValidator clientValidator;

    public ClientServiceImpl(TcpClient tcpClient, ExecutorService executorService) {
        this.tcpClient = tcpClient;
        this.executorService = executorService;
        this.clientJsonEncoder = new ClientJsonEncoder();
        this.clientValidator = new ClientValidator();
    }

    @Override
    public Future<List<Client>> findAll() throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.GET_ALL, "");
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<Client> clients = clientJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> clients);
    }

    @Override
    public Future<String> save(Client entity) throws ConnectionException {
        clientValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.SAVE_ONE, clientJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> update(Client entity) throws ConnectionException {
        clientValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.UPDATE_ONE, clientJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.DELETE_ONE, id.toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }
}
