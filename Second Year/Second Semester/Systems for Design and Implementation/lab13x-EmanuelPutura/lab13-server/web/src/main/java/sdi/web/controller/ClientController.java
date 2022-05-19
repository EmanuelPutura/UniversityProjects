package sdi.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.data.domain.Sort;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import sdi.core.service.ClientService;
import sdi.web.converter.ClientConverter;
import org.springframework.beans.factory.annotation.Autowired;
import sdi.web.dto.client.ClientDto;
import sdi.web.dto.client.ClientsDto;
import sdi.web.dto.client.ClientsListDto;

@RestController
public class ClientController {
    public static Logger logger = LoggerFactory.getLogger(ClientController.class);

    private final ClientService clientService;
    private final ClientConverter clientConverter;

    @Autowired
    public ClientController(ClientService clientService, ClientConverter clientConverter) {
        this.clientService = clientService;
        this.clientConverter = clientConverter;
    }

    @RequestMapping(value = "clients/sortedAndFiltered")
    ClientsListDto getAllClientsSortedByLastName(@RequestParam String lastName, @RequestParam String sortingCriteria) {
        var clientsListDto = new ClientsListDto();

        var clients = clientService.findClientsByLastName(lastName, Sort.by(sortingCriteria));
        clients.forEach((client) -> {
            clientsListDto.getClients().add(clientConverter.convertModelToDto(client));
        });

        return clientsListDto;
    }

    @RequestMapping(value = "/clients")
    ClientsDto getAllClients() {
        logger.error("------> get all clients - method entered");
        var clientsDto = new ClientsDto(clientConverter.convertModelsToDtos(clientService.getAll()));
        logger.error(String.format("------> get all clients - ClientsDto: %s", clientsDto.toString()));

        return clientsDto;
    }

    @RequestMapping(value = "/clients/paginated")
    ClientsDto getAllClientsPaginated(@RequestParam Integer page, @RequestParam Integer size) {
        logger.error("------> get all clients paginated - method entered");
        var clientsDto = new ClientsDto(clientConverter.convertModelsToDtos(clientService.getAllFromPage(page, size)));
        logger.error(String.format("------> get all clients paginated - ClientsDto: %s", clientsDto.toString()));

        return clientsDto;
    }

    @RequestMapping(value = "/clients", method = RequestMethod.POST)
    ClientDto addClient(@RequestBody ClientDto clientDto) {
        logger.trace(String.format("add client - method started - client DTO: %s", clientDto.toString()));

        var client = clientConverter.convertDtoToModel(clientDto);
        var result = clientService.save(client);

        logger.trace("add client - client added");
        return clientConverter.convertModelToDto(result);
    }

    @RequestMapping(value = "/clients/{id}", method = RequestMethod.PUT)
    ClientDto updateClient(@PathVariable Long id, @RequestBody ClientDto dto) {
        logger.trace("update client - method entered");
        var clientDto = clientConverter.convertModelToDto(clientService.update(clientConverter.convertDtoToModel(dto)));
        logger.trace("update client - success");

        return clientDto;
    }

    @RequestMapping(value = "/clients/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteClient(@PathVariable Long id) {
        logger.trace("delete client - method entered");
        clientService.delete(id);
        logger.trace("delete client - success");
        return new ResponseEntity<>(HttpStatus.OK);
    }
}
