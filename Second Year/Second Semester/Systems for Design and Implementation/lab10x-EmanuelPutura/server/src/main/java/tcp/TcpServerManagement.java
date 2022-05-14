package tcp;

import domain.exceptions.ConnectionException;
import org.javatuples.Pair;
import org.json.JSONObject;
import org.springframework.stereotype.Component;
import service.ClientService;
import service.DeviceService;
import service.RepairOrderService;
import service.TechnicianService;
import utils.encoders.ClientJsonEncoder;
import utils.encoders.DeviceJsonEncoder;
import utils.encoders.RepairOrderJsonEncoder;
import utils.encoders.TechnicianJsonEncoder;
import utils.network.NetworkMessage;

import java.util.concurrent.ExecutionException;

@Component
public class TcpServerManagement {
    private final TcpServer tcpServer;

    private final ClientJsonEncoder clientJsonEncoder;
    private final DeviceJsonEncoder deviceJsonEncoder;
    private final TechnicianJsonEncoder technicianJsonEncoder;
    private final RepairOrderJsonEncoder repairOrderJsonEncoder;

    private final ClientService clientService;
    private final DeviceService deviceService;
    private final TechnicianService technicianService;
    private final RepairOrderService repairOrderService;

    public TcpServerManagement(TcpServer tcpServer, ClientService clientService, DeviceService deviceService,
                               TechnicianService technicianService, RepairOrderService repairOrderService) {
        this.tcpServer = tcpServer;
        this.clientService = clientService;
        this.deviceService = deviceService;
        this.technicianService = technicianService;
        this.repairOrderService = repairOrderService;

        this.clientJsonEncoder = new ClientJsonEncoder();
        this.deviceJsonEncoder = new DeviceJsonEncoder();
        this.technicianJsonEncoder = new TechnicianJsonEncoder();
        this.repairOrderJsonEncoder = new RepairOrderJsonEncoder();

        this.addAllHandlers();
    }

    private void addAllHandlers() {
        // client handlers
        addClientGetAllHandler();
        addClientSaveHandler();
        addClientRemoveHandler();
        addClientUpdateHandler();

        // device handlers
        addDeviceGetAllHandler();
        addDeviceSaveHandler();
        addDeviceRemoveHandler();
        addDeviceUpdateHandler();

        // technician handlers
        addTechnicianGetAllHandler();
        addTechnicianSaveHandler();
        addTechnicianRemoveHandler();
        addTechnicianUpdateHandler();

        // repair order handlers
        addRepairOrderGetAllHandler();
        addRepairOrderSaveHandler();
        addRepairOrderRemoveHandler();
        addRepairOrderUpdateHandler();

        // aggregate operations handlers
        addSearchDevicesByClientIdHandler();
        addFindAllTechnicianWorkingOnDeviceHandler();
    }

    private void addClientGetAllHandler() {
        tcpServer.addHandler(ClientService.GET_ALL, request -> {
            try {
                return new NetworkMessage(NetworkMessage.OK, clientJsonEncoder.encodeObjectsList(clientService.findAll().get()).toString());
            } catch (ExecutionException | InterruptedException | ConnectionException e) {
               System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addClientSaveHandler() {
        tcpServer.addHandler(ClientService.SAVE_ONE, request -> {
            var client = clientJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = clientService.save(client).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addClientUpdateHandler() {
        tcpServer.addHandler(ClientService.UPDATE_ONE, request -> {
            var client = clientJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = clientService.update(client).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addClientRemoveHandler() {
        tcpServer.addHandler(ClientService.DELETE_ONE, request -> {
            Long id = Long.parseLong(request.getBody());
            try {
                String response = clientService.deleteById(id).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addDeviceGetAllHandler() {
        tcpServer.addHandler(DeviceService.GET_ALL, request -> {
            try {
                return new NetworkMessage(NetworkMessage.OK, deviceJsonEncoder.encodeObjectsList(deviceService.findAll().get()).toString());
            } catch (ExecutionException | InterruptedException | ConnectionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addDeviceSaveHandler() {
        tcpServer.addHandler(DeviceService.SAVE_ONE, request -> {
            var device = deviceJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = deviceService.save(device).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addDeviceUpdateHandler() {
        tcpServer.addHandler(DeviceService.UPDATE_ONE, request -> {
            var device = deviceJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = deviceService.update(device).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addDeviceRemoveHandler() {
        tcpServer.addHandler(DeviceService.DELETE_ONE, request -> {
            Long id = Long.parseLong(request.getBody());
            try {
                String response = deviceService.deleteById(id).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addTechnicianGetAllHandler() {
        tcpServer.addHandler(TechnicianService.GET_ALL, request -> {
            try {
                return new NetworkMessage(NetworkMessage.OK, technicianJsonEncoder.encodeObjectsList(technicianService.findAll().get()).toString());
            } catch (ExecutionException | InterruptedException | ConnectionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addTechnicianSaveHandler() {
        tcpServer.addHandler(TechnicianService.SAVE_ONE, request -> {
            var technician = technicianJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = technicianService.save(technician).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addTechnicianUpdateHandler() {
        tcpServer.addHandler(TechnicianService.UPDATE_ONE, request -> {
            var technician = technicianJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = technicianService.update(technician).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addTechnicianRemoveHandler() {
        tcpServer.addHandler(TechnicianService.DELETE_ONE, request -> {
            Long id = Long.parseLong(request.getBody());
            try {
                String response = technicianService.deleteById(id).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addRepairOrderGetAllHandler() {
        tcpServer.addHandler(RepairOrderService.GET_ALL, request -> {
            try {
                return new NetworkMessage(NetworkMessage.OK, repairOrderJsonEncoder.encodeObjectsList(repairOrderService.findAll().get()).toString());
            } catch (ExecutionException | InterruptedException | ConnectionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addRepairOrderSaveHandler() {
        tcpServer.addHandler(RepairOrderService.SAVE_ONE, request -> {
            var order = repairOrderJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = repairOrderService.save(order).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addRepairOrderUpdateHandler() {
        tcpServer.addHandler(RepairOrderService.UPDATE_ONE, request -> {
            var order = repairOrderJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            try {
                String response = repairOrderService.update(order).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addRepairOrderRemoveHandler() {
        tcpServer.addHandler(RepairOrderService.DELETE_ONE, request -> {
            Long id = Long.parseLong(request.getBody());
            try {
                String response = repairOrderService.deleteById(id).get();
                return new NetworkMessage(response.equals("Error!") ? NetworkMessage.ERROR : NetworkMessage.OK, response);
            } catch (ConnectionException | InterruptedException | ExecutionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }

    private void addSearchDevicesByClientIdHandler() {
        tcpServer.addHandler(DeviceService.GET_ALL_WITH_CLIENT_ID, request -> {
        try {
            var client = clientJsonEncoder.decodeObject(new JSONObject(request.getBody()));
            return new NetworkMessage(NetworkMessage.OK, deviceJsonEncoder.encodeObjectsList(deviceService.searchByClientId(client.getId()).get()).toString());
        } catch (ExecutionException | InterruptedException | ConnectionException e) {
            System.out.println(e.getMessage());
            return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
        }
        });
    }

    private void addFindAllTechnicianWorkingOnDeviceHandler() {
        tcpServer.addHandler(RepairOrderService.GET_TECHNICIAN_WORKING_ON_DEVICE, request -> {
            try {
                var device = deviceJsonEncoder.decodeObject(new JSONObject(request.getBody()));
                System.out.println(device);
                return new NetworkMessage(NetworkMessage.OK, technicianJsonEncoder.encodeObjectsList(repairOrderService.findAllTechnicianWorkingOnDevice(device.getId()).get()).toString());
            } catch (ExecutionException | InterruptedException | ConnectionException e) {
                System.out.println(e.getMessage());
                return new NetworkMessage(NetworkMessage.ERROR, e.getMessage());
            }
        });
    }
}