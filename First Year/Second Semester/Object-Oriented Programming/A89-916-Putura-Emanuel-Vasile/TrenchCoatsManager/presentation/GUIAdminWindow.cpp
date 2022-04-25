#include "CustomButton.h"
#include "CustomLabel.h"
#include "CustomLineEdit.h"
#include "GuiAdminWindow.h"

#include <QFormLayout>
#include <QString>
#include <QHeaderView>
#include <QDebug>
#include <QBrush>
#include <QPalette>
#include <QPainter>
#include <QColor>
#include <QGradient>
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <set>
#include <algorithm>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QRgb>
#include <QFont>
#include <QFont>

#include <exceptions/ServiceException/ServiceException.h>


GuiAdminWindow::GuiAdminWindow(CoatsService& service, QWidget *parent) : IGuiWindow(parent), service(service) {
    resize(1200, 700);
    main_layout = new QVBoxLayout(this);
    mainMenu();
}

void GuiAdminWindow::mainMenu() {
    main_groupbox = new QGroupBox("Administrator Mode");
    main_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                 "font: bold Arial;"
                                 "font-size: 15px;");
    QVBoxLayout* groupbox_layout = new QVBoxLayout;

    table = new QTableWidget;
    populateTable();
    groupbox_layout->addWidget(table);
    add_button = new CustomButton("Add");
    groupbox_layout->addWidget(add_button);
    update_button = new CustomButton("Update");
    groupbox_layout->addWidget(update_button);
    remove_button = new CustomButton("Remove");
    groupbox_layout->addWidget(remove_button);
    display_button = new CustomButton("Display Statistics");
    groupbox_layout->addWidget(display_button);
    switch_button = new CustomButton("Switch");
    groupbox_layout->addWidget(switch_button);
    exit_button = new CustomButton("Exit");
    groupbox_layout->addWidget(exit_button);

    main_groupbox->setLayout(groupbox_layout);
    main_layout->addWidget(main_groupbox);
    mainMenuConnect();
}

void GuiAdminWindow::addMenu() {
    manageDataMenus(add_button, "Add");
    addMenuConnect();
}

void GuiAdminWindow::updateMenu() {
    searched_size_textbox = new CustomLineEdit;
    searched_colour_textbox = new CustomLineEdit;
    searched_price_textbox = new CustomLineEdit;
    searched_photograph_textbox = new CustomLineEdit;

    QFormLayout* details = new QFormLayout;
    auto *searched_groupbox = new QGroupBox("Current trench coat data");
    searched_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                 "font: bold Arial;"
                                 "font-size: 15px;");
    details->addRow(new CustomLabel("Current size:"), searched_size_textbox);
    details->addRow(new CustomLabel("Current colour:"), searched_colour_textbox);
    details->addRow(new CustomLabel("Current price:"), searched_price_textbox);
    details->addRow(new CustomLabel("Current photograph:"), searched_photograph_textbox);
    searched_groupbox->setLayout(details);

    manageDataMenus(update_button, "Update", false, searched_groupbox);
    updateMenuConnect();
}

void GuiAdminWindow::removeMenu() {
    manageDataMenus(remove_button, "Remove", true);
    removeMenuConnect();
}

void GuiAdminWindow::display() {
    QPieSeries* series = new QPieSeries;
    auto data = service.getData();
    std::set<std::string> uniques;

    for (const auto& element : data)
        uniques.insert(element.getSize());

    QFont font;
    font.setBold(true);

    int index = 0;
    for (const auto& size : uniques) {
        int count = std::count_if(data.begin(), data.end(), [&size](const auto& element){
            return element.getSize() == size;
        });
        QString displayed_data = QString::fromStdString(size) + " (" + QString::number(count) + ")";
        series->append(displayed_data, count);
        auto slice = series->slices().at(index);
        slice->setLabelColor(qRgba(214, 213, 225, 1));
        slice->setLabelFont(font);
        slice->setLabelVisible(true);
        index++;
    }

    QChart* sizes_chart = new QChart;
    sizes_chart->legend()->setLabelColor(qRgba(214, 213, 225, 1));
    sizes_chart->setTitleBrush(QColor(qRgba(214, 213, 225, 1)));
    sizes_chart->setTitleFont(font);
    QGradient gradient = QGradient::MidnightBloom;
    QBrush brush(gradient);
    sizes_chart->setBackgroundBrush(brush);
    sizes_chart->layout()->setContentsMargins(0, 0, 0, 0);
    sizes_chart->setBackgroundRoundness(0);

    sizes_chart->addSeries(series);
    sizes_chart->setTitle("Sizes Chart");

    QChartView* chartview = new QChartView(sizes_chart);
    main_layout->addWidget(chartview);

    back_button = new CustomButton("Back");
    main_layout->addWidget(back_button);
    connect(back_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        mainMenu();
    });
}

void GuiAdminWindow::manageDataMenus(QPushButton* &use_button, const std::string& use_case, bool remove_flag, QGroupBox* data_groupbox) {
    table = new QTableWidget;
    populateTable();
    main_layout->addWidget(table);

    QFormLayout *details = new QFormLayout;
    QHBoxLayout *buttons = new QHBoxLayout;
    QHBoxLayout *undo_redo_layout = new QHBoxLayout;

    size_textbox = new CustomLineEdit;
    details->addRow(new CustomLabel("Size:"), size_textbox);
    colour_textbox = new CustomLineEdit;
    details->addRow(new CustomLabel("Colour:"), colour_textbox);
    price_textbox = new CustomLineEdit;
    details->addRow(new CustomLabel("Price:"), price_textbox);

    if (!remove_flag) {
        quantity_textbox = new CustomLineEdit;
        details->addRow(new CustomLabel("Quantity:"), quantity_textbox);
    }

    photograph_textbox = new CustomLineEdit;
    details->addRow(new CustomLabel("Photograph link:"), photograph_textbox);

    use_button = new CustomButton(QString::fromStdString(use_case));
    buttons->addWidget(use_button);
    back_button = new CustomButton("Back");
    buttons->addWidget(back_button);

    undo_button = new CustomButton("Undo");
    undo_redo_layout->addWidget(undo_button);
    redo_button = new CustomButton("Redo");
    undo_redo_layout->addWidget(redo_button);

    if (data_groupbox) {
        main_layout->addWidget(data_groupbox);
        auto *new_data_groupbox = new QGroupBox("New trench coat data");
        new_data_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                     "font: bold Arial;"
                                     "font-size: 15px;");
        new_data_groupbox->setLayout(details);
        main_layout->addWidget(new_data_groupbox);
    }
    else main_layout->addLayout(details);
    main_layout->addLayout(buttons);
    main_layout->addLayout(undo_redo_layout);
}

void GuiAdminWindow::mainMenuConnect() {
    QObject::connect(add_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        addMenu();
    });
    QObject::connect(update_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        updateMenu();
    });
    QObject::connect(remove_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        removeMenu();
    });
    QObject::connect(display_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        display();
    });
    QObject::connect(switch_button, &QPushButton::clicked, [&](){
        emit adminSwitch();
    });
    QObject::connect(exit_button, &QPushButton::clicked, [&](){
        QWidget::close();
    });
}

void GuiAdminWindow::addMenuConnect() {
    QObject::connect(add_button, &QPushButton::clicked, [&](){
        auto size = size_textbox->text().toStdString();
        auto colour = colour_textbox->text().toStdString();
        auto price = price_textbox->text().toStdString();
        auto quantity = quantity_textbox->text().toStdString();
        auto photograph = photograph_textbox->text().toStdString();

        if (!isPositiveInteger(price)) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "The price must be a positive integer!");
            messagebox.exec();
            return;
        }
        if (!isPositiveInteger(quantity)) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "The quantity must be a positive integer!");
            messagebox.exec();
            return;
        }

        try {
            service.add(size, colour, stoi(price), stoi(quantity), photograph);
            populateTable();
        }
        catch (const ServiceException& exception) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "Operation add failed: " + QString::fromStdString(exception.getMessage()));
            messagebox.exec();
        }
    });
    QObject::connect(back_button, &QPushButton::clicked, [&](){
       clearLayout(main_layout);
       mainMenu();
    });
}

void GuiAdminWindow::updateMenuConnect() {
    QObject::connect(update_button, &QPushButton::clicked, [&](){
        auto searched_size = searched_size_textbox->text().toStdString();
        auto searched_colour = searched_colour_textbox->text().toStdString();
        auto searched_price = searched_price_textbox->text().toStdString();
        auto searched_photograph = searched_photograph_textbox->text().toStdString();

        auto size = size_textbox->text().toStdString();
        auto colour = colour_textbox->text().toStdString();
        auto price = price_textbox->text().toStdString();
        auto quantity = quantity_textbox->text().toStdString();
        auto photograph = photograph_textbox->text().toStdString();

        if (!isPositiveInteger(price) || !isPositiveInteger(searched_price)) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "The price must be a positive integer!");
            messagebox.exec();
            return;
        }
        if (!isPositiveInteger(quantity)) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "The quantity must be a positive integer!");
            messagebox.exec();
            return;
        }

        try {
            service.update(searched_size, searched_colour, stoi(searched_price), searched_photograph, size, colour, stoi(price), stoi(quantity), photograph);
            populateTable();
        }
        catch (const ServiceException& exception) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "Operation update failed: " + QString::fromStdString(exception.getMessage()));
            messagebox.exec();
        }
    });
    QObject::connect(back_button, &QPushButton::clicked, [&](){
       clearLayout(main_layout);
       mainMenu();
    });
}

void GuiAdminWindow::removeMenuConnect() {
    QObject::connect(remove_button, &QPushButton::clicked, [&](){
        auto size = size_textbox->text().toStdString();
        auto colour = colour_textbox->text().toStdString();
        auto price = price_textbox->text().toStdString();
        auto photograph = photograph_textbox->text().toStdString();

        if (!isPositiveInteger(price)) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "The price must be a positive integer!");
            messagebox.exec();
            return;
        }

        try {
            service.remove(size, colour, stoi(price), photograph);
            populateTable();
        }
        catch (const ServiceException& exception) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "Operation remove failed: " + QString::fromStdString(exception.getMessage()));
            messagebox.exec();
        }
    });
    QObject::connect(back_button, &QPushButton::clicked, [&](){
       clearLayout(main_layout);
       mainMenu();
    });
}

void GuiAdminWindow::populateTable() {
    size_t columns = 5, rows = service.getLength();
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->hide();

    table->setStyleSheet("background-color: transparent;"
                         "color: rgba(214, 213, 225, 1);"
                         "font: bold Arial;"
                         "font-size: 15px;");
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: rgba(45, 45, 45, 45)}");

    table->setColumnCount(columns);
    for (size_t i = 0; i < columns; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem();
        table->setHorizontalHeaderItem(i, item);
    }

    table->setRowCount(rows);
    for (size_t i = 0; i < rows; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem();
        table->setVerticalHeaderItem(i, item);
    }

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem();
            table->setItem(i, j, item);
        }

    std::vector<std::string> header {"Size", "Colour", "Price", "Quantity", "Photograph Link"};
    for (size_t i = 0; i < columns; ++i) {
        QTableWidgetItem* item = table->horizontalHeaderItem(i);
        item->setText(QString::fromStdString(header[i]));
    }

    auto data = service.getData();
    for (size_t i = 0; i < rows; ++i) {
        QTableWidgetItem* item = table->item(i, 0);
        item->setText(QString::fromStdString(data[i].getSize()));
        item = table->item(i, 1);
        item->setText(QString::fromStdString(data[i].getColour()));
        item = table->item(i, 2);
        item->setText(QString::number(data[i].getPrice()));
        item = table->item(i, 3);
        item->setText(QString::number(data[i].getQuantity()));
        item = table->item(i, 4);
        item->setText(QString::fromStdString(data[i].getPhotograph()));
    }
}

bool GuiAdminWindow::isPositiveInteger(const std::string &string) const {
    if (string == "") return false;
    for (size_t i = 0; i < string.length(); ++i)
        if (!isdigit(string[i])) return false;
    return true;
}


