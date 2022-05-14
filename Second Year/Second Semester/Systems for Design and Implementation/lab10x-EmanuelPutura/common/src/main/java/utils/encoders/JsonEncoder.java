package utils.encoders;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public abstract class JsonEncoder<T> {
    public abstract JSONObject encodeObject(T object);

    public abstract T decodeObject(JSONObject jsonObject);

    public JSONArray encodeObjectsList(List<T> objects) {
        JSONArray array = new JSONArray();
        objects.stream().map(this::encodeObject).forEach(array::put);
        return array;
    }

    public List<T> decodeObjectsList(JSONArray jsonArray) {
        List<T> objects = new ArrayList<>();

        IntStream.range(0, jsonArray.length()).mapToObj(jsonArray::getJSONObject).forEach(element -> {
            objects.add(decodeObject(element));
        });

        return objects;
    }
}
