package sdi.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import sdi.core.service.TechnicianService;
import sdi.web.converter.TechnicianConverter;
import org.springframework.beans.factory.annotation.Autowired;
import sdi.web.dto.client.ClientDto;
import sdi.web.dto.technician.TechnicianDto;
import sdi.web.dto.technician.TechniciansDto;

@RestController
public class TechnicianController {
    public static Logger logger = LoggerFactory.getLogger(TechnicianController.class);

    private final TechnicianService technicianService;
    private final TechnicianConverter technicianConverter;

    @Autowired
    public TechnicianController(TechnicianService technicianService, TechnicianConverter technicianConverter) {
        this.technicianService = technicianService;
        this.technicianConverter = technicianConverter;
    }

    @RequestMapping(value = "/technicians")
    TechniciansDto getAllTechnicians() {
        logger.trace("get all technicians - method entered");

        return new TechniciansDto(technicianConverter.convertModelsToDtos(technicianService.getAll()));
    }

    @RequestMapping(value = "/technicians/paginated")
    TechniciansDto getAllTechniciansPaginated(@RequestParam Integer page, @RequestParam Integer size) {
        logger.trace("get all technicians paginated - method entered");

        return new TechniciansDto(technicianConverter.convertModelsToDtos(technicianService.getAllFromPage(page, size)));
    }

    @RequestMapping(value = "/technicians/findById")
    TechnicianDto findTechnicianById(@RequestParam Long technicianId) {
        var technicianOptional = technicianService.search(technicianId);
        if (technicianOptional.isEmpty()) {
            return null;
        }

        return technicianConverter.convertModelToDto(technicianOptional.get());
    }

    @RequestMapping(value = "/technicians", method = RequestMethod.POST)
    TechnicianDto addTechnician(@RequestBody TechnicianDto technicianDto) {
        logger.trace(String.format("add technician - method started - technician DTO: %s", technicianDto.toString()));

        var technician = technicianConverter.convertDtoToModel(technicianDto);
        var result = technicianService.save(technician);
        return technicianConverter.convertModelToDto(result);
    }

    @RequestMapping(value = "/technicians/{id}", method = RequestMethod.PUT)
    TechnicianDto updateTechnician(@PathVariable Long id, @RequestBody TechnicianDto dto) {
        logger.trace("update technician - method entered");

        return technicianConverter.convertModelToDto(technicianService.update(technicianConverter.convertDtoToModel(dto)));
    }

    @RequestMapping(value = "/technicians/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteTechnician(@PathVariable Long id) {
        logger.trace("delete technician - method entered");
        technicianService.delete(id);
        logger.trace("delete technician - success");

        return new ResponseEntity<>(HttpStatus.OK);
    }
}
