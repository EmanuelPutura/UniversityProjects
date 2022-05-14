package sdi.web.converter;

import sdi.web.dto.technician.TechnicianDto;
import sdi.core.model.entities.Technician;
import org.springframework.stereotype.Component;

@Component
public class TechnicianConverter extends BaseConverter<Technician, TechnicianDto> {
    @Override
    public Technician convertDtoToModel(TechnicianDto dto) {
        var model = new Technician();

        model.setId(dto.getId());
        model.setFirstName(dto.getFirstName());
        model.setLastName(dto.getLastName());
        model.setSalary(dto.getSalary());

        return model;
    }

    @Override
    public TechnicianDto convertModelToDto(Technician technician) {
        TechnicianDto dto = new TechnicianDto(technician.getFirstName(), technician.getLastName(), technician.getSalary());
        dto.setId(technician.getId());
        return dto;
    }
}
