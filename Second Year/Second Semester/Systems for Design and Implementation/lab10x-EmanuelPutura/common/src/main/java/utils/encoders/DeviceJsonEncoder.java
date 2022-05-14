package utils.encoders;

import domain.entities.Client;
import domain.entities.Device;
import org.json.JSONObject;

public class DeviceJsonEncoder extends JsonEncoder<Device> {
    @Override
    public JSONObject encodeObject(Device device) {
        JSONObject jsonClient = new JSONObject();

        jsonClient.put("id", device.getId());
        jsonClient.put("type", device.getType());
        jsonClient.put("brand", device.getBrand());
        jsonClient.put("model", device.getModel());
        jsonClient.put("clientID", device.getClientID());

        return jsonClient;
    }

    @Override
    public Device decodeObject(JSONObject jsonObject) {
        return new Device(jsonObject.getLong("id"), jsonObject.getString("type"), jsonObject.getString("brand"),
                jsonObject.getString("model"), jsonObject.getLong("clientID"));
    }
}
