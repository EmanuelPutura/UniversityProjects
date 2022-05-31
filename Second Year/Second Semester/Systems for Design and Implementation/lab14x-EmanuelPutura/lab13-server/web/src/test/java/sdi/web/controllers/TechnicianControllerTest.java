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
import sdi.core.model.entities.Technician;
import sdi.core.service.TechnicianService;
import sdi.web.controller.TechnicianController;
import sdi.web.converter.TechnicianConverter;
import sdi.web.dto.technician.TechnicianDto;

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

public class TechnicianControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private TechnicianController technicianController;

    @Mock
    private TechnicianService technicianService;

    @Mock
    private TechnicianConverter technicianConverter;

    private Technician technician1;
    private Technician technician2;

    private TechnicianDto technicianDto1;
    private TechnicianDto technicianDto2;

    private String toJsonString(TechnicianDto dto) {
        try {
            return new ObjectMapper().writeValueAsString(dto);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    private TechnicianDto convertTechnicianToTechnicianDto(Technician technician) {
        TechnicianDto dto = new TechnicianDto(technician.getFirstName(), technician.getLastName(), technician.getSalary());
        dto.setId(technician.getId());
        return dto;
    }

    private void initData() {
        technician1 = new Technician();
        technician1.setId(1L);
        technician1.setFirstName("TF1");
        technician1.setLastName("TL1");
        technician1.setSalary(100L);

        technician2 = new Technician();
        technician2.setId(2L);
        technician2.setFirstName("TF2");
        technician2.setLastName("TL2");
        technician2.setSalary(200L);

        technicianDto1 = convertTechnicianToTechnicianDto(technician1);
        technicianDto2 = convertTechnicianToTechnicianDto(technician2);
    }

    @Before
    public void setup() throws Exception {
        MockitoAnnotations.openMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(technicianController)
                .build();
        initData();
    }

    @Test
    public void getTechnicians() throws Exception {
        var technicians = Arrays.asList(technician1, technician2);
        Set<TechnicianDto> technicianDtos = new HashSet<>(Arrays.asList(technicianDto1, technicianDto2));

        when(technicianService.getAll()).thenReturn(technicians);
        when(technicianConverter.convertModelsToDtos(technicians)).thenReturn(technicianDtos);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders.get("/technicians")
                        .param("page", "0")
                        .param("pageSize", "100")
                ).andDo(print())
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.technicians", hasSize(2)))
                .andExpect(jsonPath("$.technicians[0].id", anyOf(is(1), is(2))))
                .andExpect(jsonPath("$.technicians[0].firstName", anyOf(is("TF1"), is("TF2"))));
        String result = resultActions.andReturn().getResponse().getContentAsString();

        verify(technicianService, times(1)).getAll();
        verify(technicianConverter, times(1)).convertModelsToDtos(technicians);
        verifyNoMoreInteractions(technicianService, technicianConverter);
    }

    @Test
    public void addTechnician() throws Exception {
        when(technicianConverter.convertModelToDto(technician1)).thenReturn(technicianDto1);
        when(technicianConverter.convertDtoToModel(technicianDto1)).thenReturn(technician1);
        when(technicianService.save(technician1)).thenReturn(technician1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .post("/technicians", technicianDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(technicianDto1)));

        verify(technicianService, times(1)).save(technician1);
        verify(technicianConverter, times(1)).convertModelToDto(technician1);
        verify(technicianConverter, times(1)).convertDtoToModel(technicianDto1);
        verifyNoMoreInteractions(technicianService, technicianConverter);
    }

    @Test
    public void updateTechnician() throws Exception {
        when(technicianConverter.convertModelToDto(technician1)).thenReturn(technicianDto1);
        when(technicianConverter.convertDtoToModel(technicianDto1)).thenReturn(technician1);
        when(technicianService.update(technician1)).thenReturn(technician1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .put("/technicians/{id}", technician1.getId(), technicianDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(technicianDto1)));

        verify(technicianService, times(1)).update(technician1);
        verify(technicianConverter, times(1)).convertModelToDto(technician1);
        verify(technicianConverter, times(1)).convertDtoToModel(technicianDto1);
        verifyNoMoreInteractions(technicianService, technicianConverter);
    }

    @Test
    public void deleteTechnician() throws Exception {
        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/technicians/{id}", technician1.getId(), technicianDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8));

        verify(technicianService, times(1)).delete(1L);
        verifyNoMoreInteractions(technicianService, technicianConverter);
    }
}
