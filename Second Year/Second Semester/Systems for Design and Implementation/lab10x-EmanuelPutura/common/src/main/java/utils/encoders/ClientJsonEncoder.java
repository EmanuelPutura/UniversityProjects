package utils.encoders;

import domain.entities.Client;
import org.json.JSONObject;

public class ClientJsonEncoder extends JsonEncoder<Client> {
    @Override
    public JSONObject encodeObject(Client client) {
        JSONObject jsonClient = new JSONObject();

        jsonClient.put("id", client.getId());
        jsonClient.put("firstName", client.getFirstName());
        jsonClient.put("lastName", client.getLastName());
        jsonClient.put("phoneNumber", client.getPhoneNumber());
        jsonClient.put("emailAddress", client.getEmailAddress());
        jsonClient.put("homeAddress", client.getHomeAddress());

        return jsonClient;
    }

    @Override
    public Client decodeObject(JSONObject jsonObject) {
        return new Client(jsonObject.getLong("id"), jsonObject.getString("firstName"), jsonObject.getString("lastName"),
                jsonObject.getString("phoneNumber"), jsonObject.getString("emailAddress"), jsonObject.getString("homeAddress"));
    }
}
