package sdi.web.controllers;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.ResultActions;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.model.entities.Technician;
import sdi.core.service.WorkshopTeamService;
import sdi.web.controller.WorkshopTeamController;
import sdi.web.converter.WorkshopTeamConverter;
import sdi.web.dto.teams.WorkshopTeamDto;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.hamcrest.CoreMatchers.anyOf;
import static org.hamcrest.collection.IsCollectionWithSize.hasSize;
import static org.hamcrest.core.Is.is;
import static org.mockito.Mockito.*;
import static org.mockito.Mockito.verifyNoMoreInteractions;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.print;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;

public class WorkshopTeamControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private WorkshopTeamController workshopTeamController;

    @Mock
    private WorkshopTeamService workshopTeamService;

    @Mock
    private WorkshopTeamConverter workshopTeamConverter;

    private WorkshopTeam workshopTeam1;
    private WorkshopTeam workshopTeam2;

    private WorkshopTeamDto workshopTeamDto1;
    private WorkshopTeamDto workshopTeamDto2;

    private String toJsonString(WorkshopTeamDto dto) {
        try {
            return new ObjectMapper().writeValueAsString(dto);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    private void initData() {
        var technician1 = new Technician();
        technician1.setId(1L);

        var technician2 = new Technician();
        technician2.setId(2L);

        workshopTeam1 = new WorkshopTeam();
        workshopTeam1.setId(1L);
        workshopTeam1.setTeamName("T1");
        workshopTeam1.setTeamTechnician(technician1);

        workshopTeam2 = new WorkshopTeam();
        workshopTeam2.setId(2L);
        workshopTeam2.setTeamName("T2");
        workshopTeam2.setTeamTechnician(technician2);

        workshopTeamDto1 = convertWorkshopTeamToWorkshopTeamDto(workshopTeam1);
        workshopTeamDto2 = convertWorkshopTeamToWorkshopTeamDto(workshopTeam2);
    }

    @Before
    public void setup() throws Exception {
        MockitoAnnotations.openMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(workshopTeamController)
                .build();
        initData();
    }

    private WorkshopTeamDto convertWorkshopTeamToWorkshopTeamDto(WorkshopTeam workshopTeam) {
        WorkshopTeamDto dto = new WorkshopTeamDto(workshopTeam.getTeamName(), workshopTeam.getTeamTechnician().getId());
        dto.setId(workshopTeam.getId());
        return dto;
    }

    @Test
    public void getWorkshopTeams() throws Exception {
        var workshopTeams = Arrays.asList(workshopTeam1, workshopTeam2);
        Set<WorkshopTeamDto> workshopTeamDtos = new HashSet<>(Arrays.asList(workshopTeamDto1, workshopTeamDto2));

        when(workshopTeamService.getAll()).thenReturn(workshopTeams);
        when(workshopTeamConverter.convertModelsToDtos(workshopTeams)).thenReturn(workshopTeamDtos);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders.get("/teams")
                ).andDo(print())
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.teams", hasSize(2)))
                .andExpect(jsonPath("$.teams[0].id", anyOf(is(1), is(2))))
                .andExpect(jsonPath("$.teams[0].teamName", anyOf(is("T1"), is("T2"))));
        String result = resultActions.andReturn().getResponse().getContentAsString();

        verify(workshopTeamService, times(1)).getAll();
        verify(workshopTeamConverter, times(1)).convertModelsToDtos(workshopTeams);
        verifyNoMoreInteractions(workshopTeamService, workshopTeamConverter);
    }

    @Test
    public void addWorkshopTeam() throws Exception {
        when(workshopTeamConverter.convertModelToDto(workshopTeam1)).thenReturn(workshopTeamDto1);
        when(workshopTeamConverter.convertDtoToModel(workshopTeamDto1)).thenReturn(workshopTeam1);
        when(workshopTeamService.save(workshopTeam1)).thenReturn(workshopTeam1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .post("/teams", workshopTeamDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(workshopTeamDto1)));

        verify(workshopTeamService, times(1)).save(workshopTeam1);
        verify(workshopTeamConverter, times(1)).convertModelToDto(workshopTeam1);
        verify(workshopTeamConverter, times(1)).convertDtoToModel(workshopTeamDto1);
        verifyNoMoreInteractions(workshopTeamService, workshopTeamConverter);
    }

    @Test
    public void updateWorkshopTeam() throws Exception {
        when(workshopTeamConverter.convertModelToDto(workshopTeam1)).thenReturn(workshopTeamDto1);
        when(workshopTeamConverter.convertDtoToModel(workshopTeamDto1)).thenReturn(workshopTeam1);
        when(workshopTeamService.update(workshopTeam1)).thenReturn(workshopTeam1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .put("/teams/{id}", workshopTeam1.getId(), workshopTeamDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(workshopTeamDto1)));

        verify(workshopTeamService, times(1)).update(workshopTeam1);
        verify(workshopTeamConverter, times(1)).convertModelToDto(workshopTeam1);
        verify(workshopTeamConverter, times(1)).convertDtoToModel(workshopTeamDto1);
        verifyNoMoreInteractions(workshopTeamService, workshopTeamConverter);
    }

    @Test
    public void deleteWorkshopTeam() throws Exception {
        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/teams/{id}", workshopTeam1.getId(), workshopTeamDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8));

        verify(workshopTeamService, times(1)).delete(1L);
        verifyNoMoreInteractions(workshopTeamService, workshopTeamConverter);
    }
}
