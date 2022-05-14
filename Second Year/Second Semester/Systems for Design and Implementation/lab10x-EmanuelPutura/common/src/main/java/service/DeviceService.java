package service;

import domain.entities.Device;
import domain.exceptions.ConnectionException;

import java.util.List;
import java.util.concurrent.Future;

public interface DeviceService extends GenericService<Long, Device> {
    String GET_ALL = "getDevices";
    String SAVE_ONE = "saveDevice";
    String UPDATE_ONE = "updateDevice";
    String DELETE_ONE = "deleteDevice";
    String GET_ALL_WITH_CLIENT_ID = "getAllWithClientId";

    Future<List<Device>> searchByClientId(Long clientId) throws ConnectionException;
}
