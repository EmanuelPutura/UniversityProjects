package sdi.web.dto.technician;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class TechniciansDto {
    private Set<TechnicianDto> technicians;
}
