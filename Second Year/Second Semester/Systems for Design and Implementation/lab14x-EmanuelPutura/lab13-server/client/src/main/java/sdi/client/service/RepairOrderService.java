package sdi.client.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import sdi.core.model.entities.Technician;
import sdi.web.dto.device.DevicesInsertDto;
import sdi.web.dto.orders.RepairOrderDto;
import sdi.web.dto.orders.RepairOrdersDto;
import sdi.web.dto.technician.TechnicianDto;
import sdi.web.dto.technician.TechniciansDto;

import java.util.ArrayList;
import java.util.List;

@Service
public class RepairOrderService implements CrudService<RepairOrderDto> {
    private final String ORDER_API_URL = "http://localhost:8080/api/orders";
    private final RestTemplate restTemplate;

    @Autowired
    public RepairOrderService(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @Override
    public List<RepairOrderDto> getAll() {
        RepairOrdersDto ordersDto = restTemplate.getForObject(ORDER_API_URL, RepairOrdersDto.class);

        if (ordersDto == null || ordersDto.getOrders() == null)
            return null;

        return new ArrayList<>(ordersDto.getOrders());
    }

    @Override
    public RepairOrderDto save(RepairOrderDto entity) {
        return restTemplate.postForObject(ORDER_API_URL, entity, RepairOrderDto.class);
    }

    @Override
    public RepairOrderDto update(RepairOrderDto entity) {
        restTemplate.put(ORDER_API_URL + "/{technicianId}/{deviceId}", entity, entity.getTechnicianId(), entity.getDeviceId());
        return restTemplate.getForObject(ORDER_API_URL, RepairOrderDto.class);
    }

    @Override
    public void deleteById(Long id) {
    }

    public void deleteByIds(Long technicianId, Long deviceId) {
        restTemplate.delete(ORDER_API_URL + "/{technicianId}/{deviceId}", technicianId, deviceId);
    }

    public List<TechnicianDto> findAllTechnicianWorkingOnDevice(Long deviceId) {
        var techniciansDto = restTemplate.getForObject(ORDER_API_URL + "/forDevice?deviceId={deviceId}", TechniciansDto.class, deviceId);
        if (techniciansDto == null || techniciansDto.getTechnicians() == null)
            return null;

        return new ArrayList<>(techniciansDto.getTechnicians());
    }
}
