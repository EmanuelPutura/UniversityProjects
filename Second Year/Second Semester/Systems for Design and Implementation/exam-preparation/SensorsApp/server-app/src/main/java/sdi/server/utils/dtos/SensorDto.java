package sdi.server.utils.dtos;

import org.json.JSONObject;

public class SensorDto {
    private Integer id;
    private String name;
    private Double measurement;

    public SensorDto(Integer id, String name, Double measurement) {
        this.id = id;
        this.name = name;
        this.measurement = measurement;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Double getMeasurement() {
        return measurement;
    }

    public void setMeasurement(Double measurement) {
        this.measurement = measurement;
    }

    public JSONObject encodeAsJson() {
        JSONObject jsonSensor = new JSONObject();

        jsonSensor.put("id", id);
        jsonSensor.put("name", name);
        jsonSensor.put("measurement", measurement);

        return jsonSensor;
    }

    public static SensorDto decodeFromJson(JSONObject jsonObject) {
        return new SensorDto(jsonObject.getInt("id"), jsonObject.getString("name"), jsonObject.getDouble("measurement"));
    }
}

