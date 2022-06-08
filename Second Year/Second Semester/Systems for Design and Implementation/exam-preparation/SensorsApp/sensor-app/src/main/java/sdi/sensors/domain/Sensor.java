package sdi.sensors.domain;

public class Sensor extends BaseEntity<Integer> {
    private Integer id;
    private String name;
    private Double lowerBound;
    private Double upperBound;

    public Sensor(Integer id, String name, Double lowerBound, Double upperBound) {
        this.id = id;
        this.name = name;
        this.lowerBound = lowerBound;
        this.upperBound = upperBound;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Double getLowerBound() {
        return lowerBound;
    }

    public void setLowerBound(Double lowerBound) {
        this.lowerBound = lowerBound;
    }

    public Double getUpperBound() {
        return upperBound;
    }

    public void setUpperBound(Double upperBound) {
        this.upperBound = upperBound;
    }
}
