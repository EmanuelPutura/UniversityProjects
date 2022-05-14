package sdi.web.dto.client;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import sdi.core.model.entities.Client;

import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class ClientsListDto {
    private List<ClientDto> clients = new ArrayList<>();
}
