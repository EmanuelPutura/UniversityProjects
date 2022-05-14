package service;

import domain.entities.Client;
import domain.entities.Technician;
import domain.exceptions.ConnectionException;
import domain.validators.ClientValidator;
import domain.validators.TechnicianValidator;
import org.json.JSONArray;
import org.springframework.stereotype.Service;
import tcp.TcpClient;
import utils.encoders.ClientJsonEncoder;
import utils.encoders.TechnicianJsonEncoder;
import utils.network.NetworkMessage;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class TechnicianServiceImpl implements TechnicianService {
    private final TcpClient tcpClient;
    private final ExecutorService executorService;
    private final TechnicianJsonEncoder technicianJsonEncoder;
    private final TechnicianValidator technicianValidator;

    public TechnicianServiceImpl(TcpClient tcpClient, ExecutorService executorService) {
        this.tcpClient = tcpClient;
        this.executorService = executorService;
        this.technicianJsonEncoder = new TechnicianJsonEncoder();
        this.technicianValidator = new TechnicianValidator();
    }

    @Override
    public Future<List<Technician>> findAll() throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.GET_ALL, "");
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<Technician> technicians = technicianJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> technicians);
    }

    @Override
    public Future<String> save(Technician entity) throws ConnectionException {
        technicianValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.SAVE_ONE, technicianJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> update(Technician entity) throws ConnectionException {
        technicianValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.UPDATE_ONE, technicianJsonEncoder.encodeObject(entity).toString());
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
