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
import sdi.core.model.entities.Device;
import sdi.core.service.ClientService;
import sdi.core.service.DeviceService;
import sdi.web.controller.DeviceController;
import sdi.web.converter.DeviceConverter;
import sdi.web.dto.device.DeviceDto;
import sdi.web.dto.device.DeviceInsertDto;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

import static org.hamcrest.CoreMatchers.anyOf;
import static org.hamcrest.collection.IsCollectionWithSize.hasSize;
import static org.hamcrest.core.Is.is;
import static org.mockito.Mockito.*;
import static org.mockito.Mockito.verifyNoMoreInteractions;
import static org.springframework.test.web.servlet.result.MockMvcResultHandlers.print;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.jsonPath;

public class DeviceControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private DeviceController deviceController;

    @Mock
    private DeviceService deviceService;

    @Mock
    private ClientService clientService;

    @Mock
    private DeviceConverter deviceConverter;

    private Device device1;
    private Device device2;

    private DeviceInsertDto deviceDto1;
    private DeviceInsertDto deviceDto2;

    private String toJsonString(DeviceInsertDto dto) {
        try {
            return new ObjectMapper().writeValueAsString(dto);
        } catch (JsonProcessingException e) {
            throw new RuntimeException(e);
        }
    }

    private void initData() {
        var client1 = new Client();
        var client2 = new Client();

        client1.setId(1L);
        client2.setId(2L);

        device1 = new Device();
        device1.setId(1L);
        device1.setType("T1");
        device1.setBrand("B1");
        device1.setModel("M1");
        device1.setClient(client1);

        device2 = new Device();
        device2.setId(2L);
        device2.setType("T2");
        device2.setBrand("B2");
        device2.setModel("M2");
        device2.setClient(client2);

        deviceDto1 = convertDeviceToDeviceInsertDto(device1);
        deviceDto2 = convertDeviceToDeviceInsertDto(device2);
    }

    @Before
    public void setup() throws Exception {
        MockitoAnnotations.openMocks(this);
        this.mockMvc = MockMvcBuilders
                .standaloneSetup(deviceController)
                .build();
        initData();
    }

    private DeviceInsertDto convertDeviceToDeviceInsertDto(Device device) {
        DeviceInsertDto dto = new DeviceInsertDto(device.getType(), device.getBrand(), device.getModel(), device.getClient().getId());
        dto.setId(device.getId());
        return dto;
    }

    private DeviceDto convertDeviceToDeviceDto(Device device) {
        var dto = new DeviceDto(device.getType(), device.getBrand(), device.getModel(), device.getClient());
        dto.setId(device.getId());
        return dto;
    }

    @Test
    public void getDevices() throws Exception {
        var devices = Arrays.asList(device1, device2);
        Set<DeviceInsertDto> deviceDtos = new HashSet<>(Arrays.asList(deviceDto1, deviceDto2));

        when(deviceService.getAll()).thenReturn(devices);
        when(deviceConverter.convertModelToDeviceInsertDtos(devices)).thenReturn(deviceDtos);

        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders.get("/devices")
                        .param("page", "0")
                        .param("pageSize", "100")
                ).andDo(print())
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$.devices", hasSize(2)))
                .andExpect(jsonPath("$.devices[0].id", anyOf(is(1), is(2))))
                .andExpect(jsonPath("$.devices[0].brand", anyOf(is("B1"), is("B2"))));
        String result = resultActions.andReturn().getResponse().getContentAsString();

        verify(deviceService, times(1)).getAll();
    }

//    @Test
//    public void addDevice() throws Exception {
//        when(deviceConverter.convertDtoToModel(convertDeviceToDeviceDto(device1))).thenReturn(device1);
//        when(deviceService.save(device1)).thenReturn(device1);
//        when(clientService.search(1L)).thenReturn(Optional.of(device1.getClient()));
//        when(deviceConverter.convertModelToDeviceInsertDto(device1)).thenReturn(deviceDto1);
//        when(deviceConverter.convertDeviceInsertDtoToDeviceDto(deviceDto1, device1.getClient())).thenReturn(convertDeviceToDeviceDto(device1));
//
//        ResultActions resultActions = mockMvc
//                .perform(MockMvcRequestBuilders
//                        .post("/devices", deviceDto1)
//                        .contentType(MediaType.APPLICATION_JSON_UTF8)
//                        .content(toJsonString(deviceDto1)));
//
//        verify(deviceService, times(1)).save(device1);
//        verify(deviceConverter, times(1)).convertModelToDeviceInsertDto(device1);
//        verify(deviceConverter, times(1)).convertDtoToModel(convertDeviceToDeviceDto(device1));
//        verifyNoMoreInteractions(deviceService, deviceConverter);
//    }

//    @Test
//    public void updateClient() throws Exception {
//        when(deviceConverter.convertModelToDto(device1)).thenReturn(deviceDto1);
//        when(deviceConverter.convertDtoToModel(deviceDto1)).thenReturn(device1);
//        when(deviceService.update(device1)).thenReturn(device1);
//
//        ResultActions resultActions = mockMvc
//                .perform(MockMvcRequestBuilders
//                        .put("/devices/{id}", device1.getId(), deviceDto1)
//                        .contentType(MediaType.APPLICATION_JSON_UTF8)
//                        .content(toJsonString(deviceDto1)));
//
//        verify(deviceService, times(1)).update(device1);
//        verify(deviceConverter, times(1)).convertModelToDto(device1);
//        verify(deviceConverter, times(1)).convertDtoToModel(deviceDto1);
//        verifyNoMoreInteractions(deviceService, deviceConverter);
//    }

    @Test
    public void deleteDevice() throws Exception {
        ResultActions resultActions = mockMvc
                .perform(MockMvcRequestBuilders
                        .delete("/devices/{id}", device1.getId(), deviceDto1)
                        .contentType(MediaType.APPLICATION_JSON_UTF8));

        verify(deviceService, times(1)).delete(1L);
        verifyNoMoreInteractions(deviceService, deviceConverter);
    }
}
