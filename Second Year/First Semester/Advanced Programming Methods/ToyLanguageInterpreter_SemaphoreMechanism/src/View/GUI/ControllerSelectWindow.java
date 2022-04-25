package View.GUI;

import Controller.Controller;
import Model.Statements.IStatement;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.util.List;


public class ControllerSelectWindow {
    @FXML
    private ListView<IStatement> list_view;
    private ObservableList<IStatement> statements;
    private List<Controller> controllers;

    public ControllerSelectWindow() {
        this.statements = FXCollections.observableArrayList();
    }

    @FXML
    public void initialize() {
        list_view.setItems(statements);
        list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        list_view.getSelectionModel().selectIndices(0);

        list_view.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<IStatement>() {
            @Override
            public void changed(ObservableValue<? extends IStatement> observable, IStatement old_statement, IStatement new_statement) {
                try {
                    Stage new_window = new Stage();
                    FXMLLoader loader = new FXMLLoader(new File("src/View/GUI/MainWindow.fxml").toURI().toURL());
                    GridPane root = (GridPane) loader.load();

                    ControllerMainWindow main_window_controller = loader.getController();
                    int index = list_view.getSelectionModel().getSelectedIndices().get(0);
                    main_window_controller.setController(controllers.get(index));

                    Scene scene = new Scene(root,400,150);
                    scene.getStylesheets().add(new File("src/View/GUI/MainWindow.css").toURI().toURL().toExternalForm());

                    new_window.setScene(scene);
                    new_window.setWidth(1000);
                    new_window.setHeight(600);
                    new_window.setTitle("Program no. " + Integer.toString(index + 1));
                    new_window.show();
                } catch (IOException e) {
                    System.out.println(e.getMessage());
                    System.exit(-1);
                }
            }
        });
    }

    public void setPrograms(List<Controller> controllers) {
        this.controllers = controllers;
        this.statements.clear();

        for (Controller c : controllers)
            this.statements.add(c.getRepository().getInitialProgramState().getInitialStatement());
    }
}
