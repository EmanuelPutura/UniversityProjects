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
import sdi.core.model.entities.Client;
import sdi.core.service.ClientService;
import sdi.web.controller.ClientController;
import sdi.web.converter.ClientConverter;
import sdi.web.dto.client.ClientDto;

import java.util.*;

import static org.hamcrest.CoreMatchers.anyOf;
import static org.hamcrest.collection.IsCollectionWithSize.hasSize;
import static org.hamcrest.core.Is.is;
import static org.mockito.Mockito.*;
import static org.mockito.Mockito.verifyNoMoreInteractions;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.print;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;

public class ClientControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private ClientController clientController;

    @Mock
    private ClientService clientService;

    @Mock
    private ClientConverter clientConverter;

    private Client client1;
    private Client client2;

    private ClientDto clientDto1;
    private ClientDto clientDto2;

    private String toJsonString(ClientDto dto) {
        try {
            return new ObjectMapper().writeValueAsString(dto);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    private void initData() {
        client1 = new Client();
        client1.setId(1L);
        client1.setFirstName("CF1");
        client1.setLastName("CL1");
        client1.setEmailAddress("CE1");

        client2 = new Client();
        client2.setId(1L);
        client2.setFirstName("CF2");
        client2.setLastName("CL2");
        client2.setEmailAddress("CE2");

        clientDto1 = convertClientToClientDto(client1);
        clientDto2 = convertClientToClientDto(client2);
    }

    @Before
    public void setup() throws Exception {
        MockitoAnnotations.openMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(clientController)
                .build();
        initData();
    }

    private ClientDto convertClientToClientDto(Client client) {
        ClientDto dto = new ClientDto(client.getFirstName(), client.getLastName(), client.getEmailAddress());
        dto.setId(client.getId());
        return dto;
    }

    @Test
    public void getClients() throws Exception {
        var clients = Arrays.asList(client1, client2);
        Set<ClientDto> clientDtos = new HashSet<>(Arrays.asList(clientDto1, clientDto2));

        when(clientService.getAll()).thenReturn(clients);
        when(clientConverter.convertModelsToDtos(clients)).thenReturn(clientDtos);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders.get("/clients")
                        .param("page", "0")
                        .param("pageSize", "100")
                ).andDo(print())
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.clients", hasSize(2)))
                .andExpect(jsonPath("$.clients[0].id", anyOf(is(1), is(2))))
                .andExpect(jsonPath("$.clients[0].firstName", anyOf(is("CF1"), is("CF2"))));
        String result = resultActions.andReturn().getResponse().getContentAsString();

        verify(clientService, times(1)).getAll();
        verify(clientConverter, times(1)).convertModelsToDtos(clients);
        verifyNoMoreInteractions(clientService, clientConverter);
    }

    @Test
    public void addClient() throws Exception {
        when(clientConverter.convertModelToDto(client1)).thenReturn(clientDto1);
        when(clientConverter.convertDtoToModel(clientDto1)).thenReturn(client1);
        when(clientService.save(client1)).thenReturn(client1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .post("/clients", clientDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(clientDto1)));

        verify(clientService, times(1)).save(client1);
        verify(clientConverter, times(1)).convertModelToDto(client1);
        verify(clientConverter, times(1)).convertDtoToModel(clientDto1);
        verifyNoMoreInteractions(clientService, clientConverter);
    }

    @Test
    public void updateClient() throws Exception {
        when(clientConverter.convertModelToDto(client1)).thenReturn(clientDto1);
        when(clientConverter.convertDtoToModel(clientDto1)).thenReturn(client1);
        when(clientService.update(client1)).thenReturn(client1);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .put("/clients/{id}", client1.getId(), clientDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8)
                        .content(toJsonString(clientDto1)));

        verify(clientService, times(1)).update(client1);
        verify(clientConverter, times(1)).convertModelToDto(client1);
        verify(clientConverter, times(1)).convertDtoToModel(clientDto1);
        verifyNoMoreInteractions(clientService, clientConverter);
    }

    @Test
    public void deleteClient() throws Exception {
        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/clients/{id}", client1.getId(), clientDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8));

        verify(clientService, times(1)).delete(1L);
        verifyNoMoreInteractions(clientService, clientConverter);
    }
}
