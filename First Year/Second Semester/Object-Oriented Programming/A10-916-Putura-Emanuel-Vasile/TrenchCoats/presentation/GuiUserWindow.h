#ifndef GUIUSERWINDOW_H
#define GUIUSERWINDOW_H

#include "CoatsTableModel.h"
#include "IGuiWindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QGroupBox>
#include <QWidget>
#include <QShortcut>

#include <business/CoatsService.h>


class GuiUserWindow : public IGuiWindow {
private:
    CoatsService& service;

    int searching = -1;
    std::string searched_size = "";

    QVBoxLayout* main_layout;
    QGroupBox* main_groupbox;

    QTableView* table;
    CoatsTableModel* repository_model;
    CoatsTableModel* basket_model;

    QPushButton* display_button;
    QPushButton* basket_button;
    QPushButton* show_button;
    QPushButton* switch_button;
    QPushButton* exit_button;
    QPushButton* back_button;
    QPushButton* search_button;
    QPushButton* add_button;
    QPushButton* skip_button;
    QPushButton* stop_button;
    QPushButton* undo_button;
    QPushButton* redo_button;

    QLineEdit* search_textbox;
    QLineEdit* size_textbox;
    QLineEdit* colour_textbox;
    QLineEdit* price_textbox;
    QLineEdit* quantity_textbox;
    QLineEdit* link_textbox;
    QLineEdit* payment_textbox;

    QGroupBox* details_groupbox;
    QGroupBox* search_groupbox;

    QShortcut *undo_shortcut;
    QShortcut *redo_shortcut;
public:
    explicit GuiUserWindow(CoatsService& service, QWidget *parent = 0);
private:
    void mainMenu();
    void display() override;
    void shoppingBasket();

    void mainMenuConnect();
    void displayMenuConnect();
};

#endif // GUIUSERWINDOW_H
