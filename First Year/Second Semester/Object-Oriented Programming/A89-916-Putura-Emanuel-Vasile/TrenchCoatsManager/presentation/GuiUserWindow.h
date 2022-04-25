#ifndef GUIUSERWINDOW_H
#define GUIUSERWINDOW_H

#include "IGuiWindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QGroupBox>
#include <QWidget>

#include <business/CoatsService.h>


class GuiUserWindow : public IGuiWindow {
private:
    CoatsService& service;

    int searching = -1;
    std::string searched_size = "";

    QVBoxLayout* main_layout;
    QGroupBox* main_groupbox;

    QTableWidget* table;
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

    QLineEdit* search_textbox;
    QLineEdit* size_textbox;
    QLineEdit* colour_textbox;
    QLineEdit* price_textbox;
    QLineEdit* quantity_textbox;
    QLineEdit* link_textbox;
    QLineEdit* payment_textbox;

    QGroupBox* details_groupbox;
    QGroupBox* search_groupbox;
public:
    explicit GuiUserWindow(CoatsService& service, QWidget *parent = 0);
private:
    void mainMenu();
    void display() override;
    void shoppingBasket();
    void show();

    void mainMenuConnect();
    void displayMenuConnect();
    void populateTable(bool from_service = true, std::vector<TrenchCoat> data = std::vector<TrenchCoat>());
};

#endif // GUIUSERWINDOW_H
