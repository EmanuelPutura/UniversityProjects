package view;

import domain.exceptions.ConnectionException;
import domain.exceptions.WorkshopException;

import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

public interface GenericConsole {
    void addEntity();

    void updateEntity();

    void deleteEntity();

    void printAllEntities();
}
