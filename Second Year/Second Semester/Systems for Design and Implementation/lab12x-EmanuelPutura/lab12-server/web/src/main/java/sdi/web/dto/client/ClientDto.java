package sdi.web.dto.client;

import lombok.*;
import sdi.web.dto.BaseDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class ClientDto extends BaseDto {
    private String firstName;
    private String lastName;
    private String emailAddress;
}
