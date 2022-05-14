package service;

import domain.entities.Client;
import domain.entities.Device;
import domain.entities.RepairOrder;
import domain.entities.Technician;
import domain.exceptions.ConnectionException;
import domain.validators.ClientValidator;
import domain.validators.RepairOrderValidator;
import org.json.JSONArray;
import org.springframework.stereotype.Service;
import tcp.TcpClient;
import utils.encoders.ClientJsonEncoder;
import utils.encoders.DeviceJsonEncoder;
import utils.encoders.RepairOrderJsonEncoder;
import utils.encoders.TechnicianJsonEncoder;
import utils.network.NetworkMessage;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class RepairOrderServiceImpl implements RepairOrderService {
    private final TcpClient tcpClient;
    private final ExecutorService executorService;

    private final RepairOrderJsonEncoder repairOrderJsonEncoder;
    private final DeviceJsonEncoder deviceJsonEncoder;
    private final TechnicianJsonEncoder technicianJsonEncoder;

    private final RepairOrderValidator repairOrderValidator;

    public RepairOrderServiceImpl(TcpClient tcpClient, ExecutorService executorService) {
        this.tcpClient = tcpClient;
        this.executorService = executorService;

        this.repairOrderJsonEncoder = new RepairOrderJsonEncoder();
        this.deviceJsonEncoder = new DeviceJsonEncoder();
        this.technicianJsonEncoder = new TechnicianJsonEncoder();

        this.repairOrderValidator = new RepairOrderValidator();
    }

    @Override
    public Future<List<RepairOrder>> findAll() throws ConnectionException {
        NetworkMessage request = new NetworkMessage(this.GET_ALL, "");
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<RepairOrder> orders = repairOrderJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> orders);
    }

    @Override
    public Future<String> save(RepairOrder entity) throws ConnectionException {
        repairOrderValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.SAVE_ONE, repairOrderJsonEncoder.encodeObject(entity).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);

        return executorService.submit(response::getHeader);
    }

    @Override
    public Future<String> update(RepairOrder entity) throws ConnectionException {
        repairOrderValidator.validate(entity);

        NetworkMessage request = new NetworkMessage(this.UPDATE_ONE, repairOrderJsonEncoder.encodeObject(entity).toString());
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
    public Future<List<Technician>> findAllTechnicianWorkingOnDevice(Long deviceId) throws ConnectionException {
        var deviceDto = new Device(deviceId, "", "", "", 0L);
        NetworkMessage request = new NetworkMessage(this.GET_TECHNICIAN_WORKING_ON_DEVICE, deviceJsonEncoder.encodeObject(deviceDto).toString());
        NetworkMessage response = tcpClient.sendAndReceive(request);
        String jsonText = response.getBody();

        List<Technician> technicians = technicianJsonEncoder.decodeObjectsList(new JSONArray(jsonText));
        return executorService.submit(() -> technicians);
    }
}
