package View.GUI;

import Model.Statements.IStatement;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;


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
                System.out.println("...test");
            }
        });
    }

    public void setStatements(ObservableList<IStatement> statements) {
        this.statements = statements;
    }
}
