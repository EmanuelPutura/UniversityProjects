package utils;

public class IfThenPair {
    private final Boolean ifCondition;
    private final String thenError;

    public IfThenPair(Boolean cond, String then){
        this.ifCondition = cond;
        this.thenError = then;
    }

    public Boolean getIfCondition() {
        return ifCondition;
    }

    public String getThenError() {
        return thenError;
    }

}