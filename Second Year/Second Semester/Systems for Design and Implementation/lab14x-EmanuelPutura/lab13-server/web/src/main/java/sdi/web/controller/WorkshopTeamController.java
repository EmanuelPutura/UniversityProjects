package sdi.web.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import sdi.core.service.WorkshopTeamService;
import sdi.web.converter.WorkshopTeamConverter;
import sdi.web.dto.teams.WorkshopTeamDto;
import sdi.web.dto.teams.WorkshopTeamDtos;

@RestController
public class WorkshopTeamController {
    public static Logger logger = LoggerFactory.getLogger(WorkshopTeamController.class);

    private final WorkshopTeamService workshopTeamService;
    private final WorkshopTeamConverter workshopTeamConverter;

    @Autowired
    public WorkshopTeamController(WorkshopTeamService workshopTeamService, WorkshopTeamConverter workshopTeamConverter) {
        this.workshopTeamService = workshopTeamService;
        this.workshopTeamConverter = workshopTeamConverter;
    }

    @RequestMapping(value = "/teams")
    WorkshopTeamDtos getAllWorkshopTeams() {
        logger.error("------> get all workshop teams - method entered");
        var teamsDto = new WorkshopTeamDtos(workshopTeamConverter.convertModelsToDtos(workshopTeamService.getAll()));
        logger.error(String.format("------> get all workshop teams - WorkshopTeamsDto: %s", teamsDto.toString()));

        return teamsDto;
    }

    @RequestMapping(value = "/teams/paginated")
    WorkshopTeamDtos getAllWorkshopTeamsPaginated(@RequestParam Integer page, @RequestParam Integer size) {
        return new WorkshopTeamDtos(workshopTeamConverter.convertModelsToDtos(workshopTeamService.getAllFromPage(page, size)));
    }

    @RequestMapping(value = "/teams", method = RequestMethod.POST)
    WorkshopTeamDto addWorkshopTeam(@RequestBody WorkshopTeamDto teamDto) {
        var team = workshopTeamConverter.convertDtoToModel(teamDto);
        var result = workshopTeamService.save(team);

        return workshopTeamConverter.convertModelToDto(result);
    }

    @RequestMapping(value = "/teams/{id}", method = RequestMethod.PUT)
    WorkshopTeamDto updateWorkshopTeam(@PathVariable Long id, @RequestBody WorkshopTeamDto dto) {
        return workshopTeamConverter.convertModelToDto(workshopTeamService.update(workshopTeamConverter.convertDtoToModel(dto)));
    }

    @RequestMapping(value = "/teams/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteWorkshopTeam(@PathVariable Long id) {
        workshopTeamService.delete(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }
}
