package service;

import domain.entities.Client;
import domain.entities.Device;
import domain.exceptions.ConnectionException;
import domain.validators.DeviceValidator;
import org.json.JSONArray;
import org.springframework.stereotype.Service;
import tcp.TcpClient;
import utils.encoders.ClientJsonEncoder;
import utils.encoders.DeviceJsonEncoder;
import utils.network.NetworkMessage;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class DeviceServiceImpl implements DeviceService {
    private final TcpClient tcpClient;
    private final ExecutorService executorService;

    private final DeviceJsonEncoder deviceJsonEncoder;
    private final ClientJsonEncoder clientJsonEncoder;

    private final DeviceValidator deviceValidator;

    public DeviceServiceImpl(TcpClient tcpClient, ExecutorService executorService) {
        this.tcpClient = tcpClient;
        this.executorService = executorService;

        this.deviceJsonEncoder = new DeviceJsonEncoder();
        this.clientJsonEncoder = new ClientJsonEncoder();

        this.deviceValidator = new DeviceValidator();
    }

    @Override
    public Future<List<Device>> findAll() throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.GET_ALL, "");
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<Device> devices = deviceJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> devices);
    }

    @Override
    public Future<String> save(Device entity) throws ConnectionException {
        deviceValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.SAVE_ONE, deviceJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> update(Device entity) throws ConnectionException {
        deviceValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.UPDATE_ONE, deviceJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.DELETE_ONE, id.toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<List<Device>> searchByClientId(Long clientId) throws ConnectionException {
        var clientDto = new Client(clientId, "", "", "", "", "");
        NetworkMessage request = new NetworkMessage(this.GET_ALL_WITH_CLIENT_ID, clientJsonEncoder.encodeObject(clientDto).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<Device> devices = deviceJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> devices);
    }
}
