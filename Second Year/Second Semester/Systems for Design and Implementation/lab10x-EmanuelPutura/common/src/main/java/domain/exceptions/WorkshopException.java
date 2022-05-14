package domain.exceptions;

public class WorkshopException extends RuntimeException {
    public WorkshopException(String message) {
        super(message);
    }

    public WorkshopException(String message, Throwable cause) {
        super(message, cause);
    }

    public WorkshopException(Throwable cause){
        super(cause);
    }
}
