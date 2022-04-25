#ifndef GUIADMINWINDOW_H
#define GUIADMINWINDOW_H

#include "IGuiWindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>
#include <string>
#include <QFormLayout>
#include <QCheckBox>

#include <business/CoatsService.h>


class GuiAdminWindow : public IGuiWindow {
private:
    CoatsService& service;

    QTableWidget* table;
    QVBoxLayout* main_layout;
    QGroupBox* main_groupbox;

    QPushButton* add_button;
    QPushButton* update_button;
    QPushButton* remove_button;
    QPushButton* display_button;
    QPushButton* switch_button;
    QPushButton* exit_button;
    QPushButton* back_button;
    QPushButton* undo_button;
    QPushButton* redo_button;

    QLineEdit* size_textbox;
    QLineEdit* colour_textbox;
    QLineEdit* price_textbox;
    QLineEdit* quantity_textbox;
    QLineEdit* photograph_textbox;
    QLineEdit* searched_size_textbox;
    QLineEdit* searched_colour_textbox;
    QLineEdit* searched_price_textbox;
    QLineEdit* searched_photograph_textbox;
public:
    explicit GuiAdminWindow(CoatsService& service, QWidget *parent = 0);
private:
    void mainMenu();
    void addMenu();
    void updateMenu();
    void removeMenu();
    void display() override;

    void manageDataMenus(QPushButton* &use_button, const std::string& use_case, bool remove_flag = false, QGroupBox* data_groupbox = nullptr);
    void populateTable();
    bool isPositiveInteger(const std::string& string) const;

    void mainMenuConnect();
    void addMenuConnect();
    void updateMenuConnect();
    void removeMenuConnect();
};

#endif // GUIADMINWINDOW_H
