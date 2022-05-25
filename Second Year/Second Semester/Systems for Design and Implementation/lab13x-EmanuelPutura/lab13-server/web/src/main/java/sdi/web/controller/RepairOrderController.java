package sdi.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import sdi.core.service.DeviceService;
import sdi.core.service.TechnicianService;
import sdi.web.converter.DeviceConverter;
import sdi.web.converter.TechnicianConverter;
import sdi.web.dto.device.DeviceInsertDto;
import sdi.web.dto.device.DeviceInsertDtos;
import sdi.web.dto.device.DevicesDto;
import sdi.web.dto.orders.RepairOrderDto;
import sdi.web.dto.orders.RepairOrdersDto;
import sdi.web.dto.technician.TechniciansDto;

@RestController
public class RepairOrderController {
    public static Logger logger = LoggerFactory.getLogger(RepairOrderController.class);

    private final DeviceService deviceService;
    private final TechnicianService technicianService;

    private final TechnicianConverter technicianConverter;
    private final DeviceConverter deviceConverter;

    @Autowired
    public RepairOrderController(DeviceService deviceService, TechnicianService technicianService, TechnicianConverter technicianConverter, DeviceConverter deviceConverter) {
        this.deviceService = deviceService;
        this.technicianService = technicianService;
        this.technicianConverter = technicianConverter;
        this.deviceConverter = deviceConverter;
    }

    @RequestMapping(value = "/orders")
    RepairOrdersDto getAllRepairOrders() {
        logger.trace("get all orders - method entered");

        RepairOrdersDto repairOrderDtos = new RepairOrdersDto();
        var devices = deviceService.getAll();
        devices.forEach((device) -> {
              var assignedTechnicians = device.getAssignedTechnicians();

              assignedTechnicians.forEach((technician -> {
                  repairOrderDtos.getOrders().add(new RepairOrderDto(technician.getId(), device.getId()));
              }));
        });

        return repairOrderDtos;
    }

    @RequestMapping(value = "/orders/forDevice")
    TechniciansDto findTechniciansWorkingOnDevice(@RequestParam Long deviceId) {
        logger.trace("get all technicians working on device - method entered");

        var device = deviceService.search(deviceId);
        if (device.isEmpty())
            return null;

        return new TechniciansDto(technicianConverter.convertModelsToDtos(technicianService.findTechniciansWorkingOnDevice(device.get())));
    }

    @RequestMapping(value = "/orders/forTechnician")
    DeviceInsertDtos findDevicesBeingWorkedOnByTechnician(@RequestParam Long technicianId) {
        var technician = technicianService.search(technicianId);
        if (technician.isEmpty())
            return null;

        return new DeviceInsertDtos(deviceConverter.convertModelsToDeviceInsertDtos(deviceService.findDevicesBeingWorkedOnByTechnician(technician.get())));
    }

    @RequestMapping(value = "/orders", method = RequestMethod.POST)
    @Transactional
    RepairOrderDto addRepairOrder(@RequestBody RepairOrderDto repairOrderDto) {
        logger.trace(String.format("add order - method started - client DTO: %s", repairOrderDto.toString()));

        var device = deviceService.search(repairOrderDto.getDeviceId());
        if (device.isEmpty())
            return null;

        var technician = technicianService.search(repairOrderDto.getTechnicianId());
        if (technician.isEmpty())
            return null;

        deviceService.addTechnician(repairOrderDto.getDeviceId(), technician.get());
        technicianService.addDevice(repairOrderDto.getTechnicianId(), device.get());

        return new RepairOrderDto(technician.get().getId(), device.get().getId());
    }

    @RequestMapping(value = "/orders/{technicianId}/{deviceId}", method = RequestMethod.PUT)
    RepairOrderDto updateRepairOrder(@PathVariable Long technicianId, @PathVariable Long deviceId, @RequestBody RepairOrderDto repairOrderDto) {
        return null;
    }

    @RequestMapping(value = "/orders/{technicianId}/{deviceId}", method = RequestMethod.DELETE)
    RepairOrderDto deleteRepairOrder(@PathVariable Long technicianId, @PathVariable Long deviceId) {
        logger.trace("delete order - method entered");

        var device = deviceService.search(deviceId);
        if (device.isEmpty())
            return null;

        var technician = technicianService.search(technicianId);
        if (technician.isEmpty())
            return null;

        deviceService.removeTechnician(deviceId, technician.get());
        technicianService.removeDevice(technicianId, device.get());

        return new RepairOrderDto(technicianId, deviceId);
    }
}
