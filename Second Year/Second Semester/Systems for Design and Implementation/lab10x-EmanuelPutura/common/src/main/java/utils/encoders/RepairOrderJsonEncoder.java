package utils.encoders;

import domain.entities.Client;
import domain.entities.RepairOrder;
import org.json.JSONObject;

public class RepairOrderJsonEncoder extends JsonEncoder<RepairOrder> {
    @Override
    public JSONObject encodeObject(RepairOrder repairOrder) {
        JSONObject jsonRepairOrder = new JSONObject();

        jsonRepairOrder.put("id", repairOrder.getId());
        jsonRepairOrder.put("deviceID", repairOrder.getDeviceID());
        jsonRepairOrder.put("technicianID", repairOrder.getTechnicianID());
        jsonRepairOrder.put("dateBrought", repairOrder.getDateBrought());
        jsonRepairOrder.put("dateExpected", repairOrder.getDateExpected());
        jsonRepairOrder.put("cost", repairOrder.getCost());

        return jsonRepairOrder;
    }

    @Override
    public RepairOrder decodeObject(JSONObject jsonObject) {
        return new RepairOrder(jsonObject.getLong("id"), jsonObject.getLong("deviceID"), jsonObject.getLong("technicianID"),
                jsonObject.getString("dateBrought"), jsonObject.getString("dateExpected"), jsonObject.getFloat("cost"));
    }
}
