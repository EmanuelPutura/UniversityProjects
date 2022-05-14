package service;

import domain.entities.RepairOrder;
import domain.entities.Technician;
import domain.exceptions.ConnectionException;

import java.util.List;
import java.util.concurrent.Future;

public interface RepairOrderService extends GenericService<Long, RepairOrder> {
    String GET_ALL = "getRepairOrders";
    String SAVE_ONE = "saveRepairOrder";
    String UPDATE_ONE = "updateRepairOrder";
    String DELETE_ONE = "deleteRepairOrder";

    String GET_TECHNICIAN_WORKING_ON_DEVICE = "getAllTechniciansWorkingOnDevice";

    Future<List<Technician>> findAllTechnicianWorkingOnDevice(Long deviceId) throws ConnectionException;
}
