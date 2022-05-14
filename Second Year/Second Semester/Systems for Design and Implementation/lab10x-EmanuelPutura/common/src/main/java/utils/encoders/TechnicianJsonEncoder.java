package utils.encoders;

import domain.entities.Client;
import domain.entities.Technician;
import org.json.JSONObject;

public class TechnicianJsonEncoder extends JsonEncoder<Technician> {
    @Override
    public JSONObject encodeObject(Technician technician) {
        JSONObject jsonTechnician = new JSONObject();

        jsonTechnician.put("id", technician.getId());
        jsonTechnician.put("firstName", technician.getFirstName());
        jsonTechnician.put("lastName", technician.getLastName());
        jsonTechnician.put("salary", technician.getSalary());
        jsonTechnician.put("phoneNumber", technician.getPhoneNumber());
        jsonTechnician.put("emailAddress", technician.getEmailAddress());
        jsonTechnician.put("homeAddress", technician.getHomeAddress());
        jsonTechnician.put("employeeNumber", technician.getEmployeeNumber());

        return jsonTechnician;
    }

    @Override
    public Technician decodeObject(JSONObject jsonObject) {
        return new Technician(jsonObject.getLong("id"), jsonObject.getString("firstName"), jsonObject.getString("lastName"), jsonObject.getLong("salary"),
                jsonObject.getString("phoneNumber"), jsonObject.getString("emailAddress"), jsonObject.getString("homeAddress"), jsonObject.getLong("employeeNumber"));
    }
}
