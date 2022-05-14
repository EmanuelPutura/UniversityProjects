package sdi.web.dto.orders;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.HashSet;
import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class RepairOrdersDto {
    private Set<RepairOrderDto> orders = new HashSet<>();
}
