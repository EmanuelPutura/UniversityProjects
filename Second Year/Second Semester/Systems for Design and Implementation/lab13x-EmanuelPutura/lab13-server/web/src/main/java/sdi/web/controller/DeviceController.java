package sdi.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import sdi.core.model.entities.Client;
import sdi.core.model.exceptions.WorkshopException;
import sdi.core.service.ClientService;
import sdi.core.service.DeviceService;
import sdi.web.converter.DeviceConverter;
import org.springframework.beans.factory.annotation.Autowired;
import sdi.web.dto.device.DeviceDto;
import sdi.web.dto.device.DeviceInsertDto;
import sdi.web.dto.device.DeviceWithClientFieldsDto;
import sdi.web.dto.device.DevicesInsertDto;

@RestController
public class DeviceController {
    public static Logger logger = LoggerFactory.getLogger(DeviceController.class);

    private final DeviceService deviceService;
    private final ClientService clientService;

    private final DeviceConverter deviceConverter;

    @Autowired
    public DeviceController(DeviceService deviceService, ClientService clientService, DeviceConverter deviceConverter) {
        this.deviceService = deviceService;
        this.clientService = clientService;
        this.deviceConverter = deviceConverter;
    }

    private DeviceDto getDeviceDtoFromDeviceInsertDto(DeviceInsertDto deviceInsertDto) {
        var clientOptional = clientService.search(deviceInsertDto.getClientId());

        if (clientOptional.isEmpty())
            throw new WorkshopException("Client does not exist!");

        Client client = clientOptional.get();
        return deviceConverter.convertDeviceInsertDtoToDeviceDto(deviceInsertDto, client);
    }

    private DeviceDto getDeviceDtoFromDeviceWithClientFieldsDto(DeviceWithClientFieldsDto deviceWithClientFieldsDto) {
        var clientOptional = clientService.findClientsByAllFieldsButForId(deviceWithClientFieldsDto.getClientLastName(),
                deviceWithClientFieldsDto.getClientFirstName(), deviceWithClientFieldsDto.getClientEmailAddress());

        if (clientOptional.isEmpty())
            throw new WorkshopException("Client does not exist!");

        Client client = clientOptional.get();
        return deviceConverter.convertDeviceWithClientFieldsDtoToDeviceDto(deviceWithClientFieldsDto, client);
    }

    @RequestMapping(value = "/devices")
    DevicesInsertDto getAllDevices() {
        logger.trace("get all devices - method entered");
        var devicesDto =new DevicesInsertDto(deviceConverter.convertModelToDeviceInsertDtos(deviceService.getAll()));
        logger.trace(String.format("get all devices - DevicesDto: %s", devicesDto.toString()));

        return devicesDto;
    }

    @RequestMapping(value = "/devices/paginated")
    DevicesInsertDto getAllDevicesPaginated(@RequestParam Integer page, @RequestParam Integer size) {
        logger.trace("get all devices paginated - method entered");
        var devicesDto =new DevicesInsertDto(deviceConverter.convertModelToDeviceInsertDtos(deviceService.getAllFromPage(page, size)));
        logger.trace(String.format("get all devices paginated - DevicesDto: %s", devicesDto.toString()));

        return devicesDto;
    }

    @RequestMapping(value="/devices/forClient")
    DevicesInsertDto getAllForClient(@RequestParam Long deviceId) {
        logger.trace("get all for client - method entered");
        return new DevicesInsertDto(deviceConverter.convertModelToDeviceInsertDtos(deviceService.findDevicesByClientId(deviceId)));
    }

    @RequestMapping(value = "/devices", method = RequestMethod.POST)
    DeviceInsertDto addDevice(@RequestBody DeviceInsertDto deviceInsertDto) {
        logger.trace(String.format("add device - method started - client DTO: %s", deviceInsertDto.toString()));

        var deviceDto = getDeviceDtoFromDeviceInsertDto(deviceInsertDto);
        var device = deviceConverter.convertDtoToModel(deviceDto);

        var result = deviceService.save(device);
        return deviceConverter.convertModelToDeviceInsertDto(result);
    }

    @RequestMapping(value = "/devices/add/withAllClientFields", method = RequestMethod.POST)
    DeviceInsertDto addDevice(@RequestBody DeviceWithClientFieldsDto deviceWithClientFieldsDto) {
        var deviceDto = getDeviceDtoFromDeviceWithClientFieldsDto(deviceWithClientFieldsDto);
        var device = deviceConverter.convertDtoToModel(deviceDto);

        var result = deviceService.save(device);
        return deviceConverter.convertModelToDeviceInsertDto(result);
    }

    @RequestMapping(value = "/devices/{id}", method = RequestMethod.PUT)
    DeviceInsertDto updateDevice(@PathVariable Long id, @RequestBody DeviceInsertDto dto) {
        logger.trace("update device - method entered");
        return deviceConverter.convertModelToDeviceInsertDto(deviceService.update(deviceConverter.convertDtoToModel(getDeviceDtoFromDeviceInsertDto(dto))));
    }

    @RequestMapping(value = "/devices/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteDevice(@PathVariable Long id) {
        logger.trace("delete device - method entered");
        deviceService.delete(id);
        logger.trace("delete device - success");

        return new ResponseEntity<>(HttpStatus.OK);
    }
}
