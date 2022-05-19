package sdi.client.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import sdi.web.dto.client.ClientDto;
import sdi.web.dto.client.ClientsDto;

import java.util.ArrayList;
import java.util.List;

@Service
public class ClientService implements CrudService<ClientDto> {
    private final String CLIENT_API_URL = "http://localhost:8080/api/clients";
    private final RestTemplate restTemplate;

    @Autowired
    public ClientService(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @Override
    public List<ClientDto> getAll() {
        ClientsDto clientsDto = restTemplate.getForObject(CLIENT_API_URL, ClientsDto.class);

        if (clientsDto == null || clientsDto.getClients() == null)
            return null;

        return new ArrayList<>(clientsDto.getClients());
    }

    @Override
    public ClientDto save(ClientDto entity) {
        return restTemplate.postForObject(CLIENT_API_URL, entity, ClientDto.class);
    }

    @Override
    public ClientDto update(ClientDto entity) {
        restTemplate.put(CLIENT_API_URL + "/{id}", entity, entity.getId());
        return restTemplate.getForObject(CLIENT_API_URL, ClientDto.class);
    }

    @Override
    public void deleteById(Long id) {
        restTemplate.delete(CLIENT_API_URL + "/{id}", id);
    }
}
