package sdi.web.converter;

import sdi.web.dto.client.ClientDto;
import sdi.core.model.entities.Client;
import org.springframework.stereotype.Component;

@Component
public class ClientConverter extends BaseConverter<Client, ClientDto> {
    @Override
    public Client convertDtoToModel(ClientDto dto) {
        var model = new Client();

        model.setId(dto.getId());
        model.setFirstName(dto.getFirstName());
        model.setLastName(dto.getLastName());
        model.setEmailAddress(dto.getEmailAddress());

        return model;
    }

    @Override
    public ClientDto convertModelToDto(Client client) {
        ClientDto dto = new ClientDto(client.getFirstName(), client.getLastName(), client.getEmailAddress());
        dto.setId(client.getId());
        return dto;
    }
}
