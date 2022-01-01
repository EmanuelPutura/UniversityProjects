package View.GUI;

import Controller.Controller;
import Controller.ControllerException;
import Model.Exceptions.ProgramException;
import Model.Program.ProgramState;
import Model.Statements.IStatement;
import Model.Values.IValue;
import Model.Values.StringValue;
import Repository.IRepository;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

public class ControllerMainWindow {
    private Controller controller;

    @FXML
    private TableView<Map.Entry<Integer, IValue>> heap_table_view;

    @FXML
    private TableColumn<Map.Entry<Integer, IValue>, Integer> heap_address_column;

    @FXML
    private TableColumn<Map.Entry<Integer, IValue>, IValue> heap_value_column;

    @FXML
    private ListView<String> out_list_view;

    @FXML
    private ListView<String> file_list_view;

    @FXML
    private ListView<ProgramState> programs_list_view;

    @FXML
    private TableView<Map.Entry<String, IValue>> sym_table_view;

    @FXML
    private TableColumn<Map.Entry<String, IValue>, String> sym_var_column;

    @FXML
    private TableColumn<Map.Entry<String, IValue>, IValue> sym_value_column;

    @FXML
    private ListView<IStatement> stack_list_view;

    @FXML
    private TextField programs_text_field;

    public void setController(Controller controller) {
        this.controller = controller;

        ObservableList<ProgramState> programs_obs = FXCollections.observableArrayList();
        programs_obs.addAll(new ArrayList<ProgramState>(controller.getRepository().getProgramStateList()));
        programs_list_view.setItems(programs_obs);
    }

    @FXML
    public void handleRunOneStepButton(ActionEvent event) {
        try {
            controller.oneStepForAllPrograms(controller.removeCompletedPrograms(controller.getRepository().getProgramStateList()));
            applyRepositoryModifications();
            programs_text_field.setText("Number of ProgramStates: " + Integer.toString(controller.getRepository().getProgramStateList().size()));
        } catch (ControllerException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("A ControllerException occurred!");
            alert.setHeaderText(e.getMessage());
            alert.showAndWait();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("An unknown exception occurred!");
            alert.setHeaderText(e.getMessage());
            alert.showAndWait();
        }
    }

    private void applyRepositoryModifications() {
        ObservableList<Map.Entry<Integer, IValue>> heap_obs = FXCollections.observableArrayList();
        heap_obs.addAll(controller.getRepository().getInitialProgramState().heapTable().getContent().entrySet());
        heap_table_view.setItems(heap_obs);

        ObservableList<String> out_obs = FXCollections.observableArrayList();
        out_obs.addAll(controller.getRepository().getInitialProgramState().outList().getInnerList().stream().map(Object::toString).collect(Collectors.toList()));
        out_list_view.setItems(out_obs);

        ObservableList<String> file_obs = FXCollections.observableArrayList();
        file_obs.addAll(controller.getRepository().getInitialProgramState().fileTable().getContent().keySet().stream().map(StringValue::toString).collect(Collectors.toList()));
        file_list_view.setItems(file_obs);

        ObservableList<ProgramState> programs_obs = FXCollections.observableArrayList();
        programs_obs.addAll(new ArrayList<ProgramState>(controller.getRepository().getProgramStateList()));
        programs_list_view.setItems(programs_obs);
    }

    @FXML
    public void initialize() {
        heap_address_column.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Map.Entry<Integer, IValue>, Integer>, ObservableValue<Integer>>() {
            @Override
            public ObservableValue<Integer> call(TableColumn.CellDataFeatures<Map.Entry<Integer, IValue>, Integer> entry) {
                Map.Entry<Integer, IValue> map_entry = entry.getValue();
                return new SimpleObjectProperty<Integer>(map_entry.getKey());
            }
        });

        heap_value_column.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Map.Entry<Integer, IValue>, IValue>, ObservableValue<IValue>>() {
            @Override
            public ObservableValue<IValue> call(TableColumn.CellDataFeatures<Map.Entry<Integer, IValue>, IValue> entry) {
                Map.Entry<Integer, IValue> map_entry = entry.getValue();
                return new SimpleObjectProperty<IValue>(map_entry.getValue());
            }
        });

        out_list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        out_list_view.getSelectionModel().selectIndices(0);

        file_list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        file_list_view.getSelectionModel().selectIndices(0);

        programs_list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        programs_list_view.getSelectionModel().selectIndices(0);

        // populate list view by calling custom function (not toString(), which is default)
        programs_list_view.setCellFactory(param -> new ListCell<ProgramState>() {
            @Override
            protected void updateItem(ProgramState item, boolean empty) {
                super.updateItem(item, empty);
                if (item == null)
                    setText(null);
                else
                    setText(Integer.toString(item.programID()));
            }
        });

        programs_list_view.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<ProgramState>() {
            @Override
            public void changed(ObservableValue<? extends ProgramState> observableValue, ProgramState old_ps, ProgramState new_ps) {
                if (new_ps == null)
                    return;

                ObservableList<Map.Entry<String, IValue>> sym_obs = FXCollections.observableArrayList();
                sym_obs.addAll(new_ps.symbolsTable().getContent().entrySet());
                sym_table_view.setItems(sym_obs);

                ObservableList<IStatement> stack_obs = FXCollections.observableArrayList();
                List<IStatement> content = new ArrayList<>(new_ps.executionStack().getContent());
                Collections.reverse(content);
                stack_obs.addAll(content);
                stack_list_view.setItems(stack_obs);
            }
        });

        sym_var_column.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Map.Entry<String, IValue>, String>, ObservableValue<String>>() {
            @Override
            public ObservableValue<String> call(TableColumn.CellDataFeatures<Map.Entry<String, IValue>, String> entry) {
                Map.Entry<String, IValue> map_entry = entry.getValue();
                return new SimpleObjectProperty<String>(map_entry.getKey());
            }
        });

        sym_value_column.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Map.Entry<String, IValue>, IValue>, ObservableValue<IValue>>() {
            @Override
            public ObservableValue<IValue> call(TableColumn.CellDataFeatures<Map.Entry<String, IValue>, IValue> entry) {
                Map.Entry<String, IValue> map_entry = entry.getValue();
                return new SimpleObjectProperty<IValue>(map_entry.getValue());
            }
        });

        stack_list_view.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        stack_list_view.getSelectionModel().selectIndices(0);
    }
}
