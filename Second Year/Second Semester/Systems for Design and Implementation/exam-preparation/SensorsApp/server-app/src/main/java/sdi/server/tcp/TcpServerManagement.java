package sdi.server.tcp;

import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.server.model.Sensor;
import sdi.server.repository.SensorRepository;
import sdi.server.utils.dtos.SensorDto;
import sdi.server.utils.network.NetworkMessage;

import java.time.LocalTime;
import java.util.Random;

@Component
public class TcpServerManagement {
    private final TcpServer tcpServer;
    private final SensorRepository sensorRepository;
    private static final String SEND_SENSOR = "SEND_SENSOR";

    @Autowired
    public TcpServerManagement(TcpServer tcpServer, SensorRepository sensorRepository) {
        this.tcpServer = tcpServer;
        this.sensorRepository = sensorRepository;
        this.addAllHandlers();
    }

    private void addAllHandlers() {
        addSendSensorsDataHandler();
    }

    private void addSendSensorsDataHandler() {
        tcpServer.addHandler(SEND_SENSOR, request -> {
            var sensorDto = SensorDto.decodeFromJson(new JSONObject(request.getBody()));
            System.out.printf("sensor-name: %s | sensor-id: %d | measurement: %f%n", sensorDto.getName(), sensorDto.getId(), sensorDto.getMeasurement());

            sensorRepository.save(new Sensor(sensorDto.getName(), sensorDto.getMeasurement(), LocalTime.now()));
            return new NetworkMessage(NetworkMessage.OK, "");
        });
    }
}
