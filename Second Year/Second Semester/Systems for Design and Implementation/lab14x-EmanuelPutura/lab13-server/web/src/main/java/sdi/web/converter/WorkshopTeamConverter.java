package sdi.web.converter;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.service.TechnicianService;
import sdi.web.dto.teams.WorkshopTeamDto;

@Component
public class WorkshopTeamConverter extends BaseConverter<WorkshopTeam, WorkshopTeamDto> {
    private final TechnicianService technicianService;

    public WorkshopTeamConverter(TechnicianService technicianService) {
        this.technicianService = technicianService;
    }

    @Override
    public WorkshopTeam convertDtoToModel(WorkshopTeamDto dto) {
        var model = new WorkshopTeam();
        var technician = technicianService.search(dto.getTechnicianId());

        if (technician.isEmpty()) {
            return null;
        }

        model.setId(dto.getId());
        model.setTeamName(dto.getTeamName());
        model.setTeamTechnician(technician.get());

        return model;
    }

    @Override
    public WorkshopTeamDto convertModelToDto(WorkshopTeam workshopTeam) {
        WorkshopTeamDto dto = new WorkshopTeamDto(workshopTeam.getTeamName(), workshopTeam.getTeamTechnician().getId());
        dto.setId(workshopTeam.getId());
        return dto;
    }
}
