package sdi.web.dto.client;

import lombok.*;
import sdi.core.model.entities.Client;
import sdi.web.dto.BaseDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class ClientDto extends BaseDto {
    private String firstName;
    private String lastName;
    private String emailAddress;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || ClientDto.class != o.getClass()) return false;
        ClientDto client = (ClientDto) o;
        return getId() != null && Objects.equals(getId(), client.getId());
    }
}
