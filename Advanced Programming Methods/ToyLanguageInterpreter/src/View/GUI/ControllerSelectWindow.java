package View.GUI;

import Model.Statements.DeclarationStatement;
import Model.Statements.IStatement;
import Model.Types.IntType;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.File;
import java.net.MalformedURLException;


public class ControllerSelectWindow {
    @FXML
    private ListView<IStatement> list_view;
    private ObservableList<IStatement> statements;

    @FXML
    public void initialize() {
        list_view.setItems(statements);
        list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        list_view.getSelectionModel().selectIndices(0);

        list_view.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<IStatement>() {
            @Override
            public void changed(ObservableValue<? extends IStatement> observable, IStatement old_statement, IStatement new_statement) {
                Stage new_window = new Stage();
                FXMLLoader loader = null;
                try {
                    loader = new FXMLLoader(new File("src/View/GUI/MainWindow.fxml").toURI().toURL());
                } catch (MalformedURLException e) {
                    System.out.println(e.getMessage());
                    System.exit(-1);
                }

                ControllerMainWindow main_window_controller = loader.getController();

                int index = list_view.getSelectionModel().getSelectedIndices().get(0) + 1;
                new_window.setTitle("Program no. " + Integer.toString(index));
                new_window.show();
            }
        });
    }

    public void setStatements(ObservableList<IStatement> statements) {
        this.statements = statements;
        list_view.setItems(statements);
    }
}
