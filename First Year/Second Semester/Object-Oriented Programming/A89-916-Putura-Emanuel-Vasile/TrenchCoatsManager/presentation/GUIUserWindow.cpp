#include "CustomButton.h"
#include "CustomLabel.h"
#include "CustomLineEdit.h"
#include "GuiUserWindow.h"

#include <QHeaderView>
#include <QDebug>
#include <QFormLayout>
#include <QMessageBox>

GuiUserWindow::GuiUserWindow(CoatsService& service, QWidget *parent) : IGuiWindow(parent), service(service) {
    resize(1200, 700);
    main_layout = new QVBoxLayout(this);
    mainMenu();
}

void GuiUserWindow::mainMenu() {
    main_groupbox = new QGroupBox("User Mode");
    main_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                 "font: bold Arial;"
                                 "font-size: 15px;");
    QVBoxLayout* groupbox_layout = new QVBoxLayout;

    table = new QTableWidget;
    populateTable();
    groupbox_layout->addWidget(table);
    display_button = new CustomButton("Display");
    groupbox_layout->addWidget(display_button);
    basket_button = new CustomButton("Show Shopping Basket");
    groupbox_layout->addWidget(basket_button);
    show_button = new CustomButton("Show Shopping Basket Externally");
    groupbox_layout->addWidget(show_button);
    switch_button = new CustomButton("Switch");
    groupbox_layout->addWidget(switch_button);
    exit_button = new CustomButton("Exit");
    groupbox_layout->addWidget(exit_button);

    main_groupbox->setLayout(groupbox_layout);
    main_layout->addWidget(main_groupbox);
    mainMenuConnect();
}

void GuiUserWindow::display() {
    table = new QTableWidget;
    populateTable();
    main_layout->addWidget(table);

    QVBoxLayout* options = new QVBoxLayout;
    QFormLayout* details = new QFormLayout;
    QGridLayout* search_details = new QGridLayout;

    details_groupbox = new QGroupBox("Found trench coat");
    details_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                 "font: bold Arial;"
                                 "font-size: 15px;");

    size_textbox = new CustomLineEdit;
    size_textbox->setReadOnly(true);
    details->addRow(new CustomLabel("Size:"), size_textbox);
    colour_textbox = new CustomLineEdit;
    colour_textbox->setReadOnly(true);
    details->addRow(new CustomLabel("Colour:"), colour_textbox);
    price_textbox = new CustomLineEdit;
    price_textbox->setReadOnly(true);
    details->addRow(new CustomLabel("Price:"), price_textbox);
    quantity_textbox = new CustomLineEdit;
    quantity_textbox->setReadOnly(true);
    details->addRow(new CustomLabel("Quantity:"), quantity_textbox);
    link_textbox = new CustomLineEdit;
    link_textbox->setReadOnly(true);
    details->addRow(new CustomLabel("Photograph link:"), link_textbox);

    details_groupbox->setLayout(details);

    back_button = new CustomButton("Back");
    add_button = new CustomButton("Add");
    skip_button = new CustomButton("Skip");
    stop_button = new CustomButton("Stop Current Search");

    options->addWidget(add_button);
    options->addWidget(skip_button);
    options->addWidget(stop_button);
    options->addWidget(back_button);

    main_layout->addWidget(details_groupbox);

    search_groupbox = new QGroupBox("Search and Payment");
    search_groupbox->setStyleSheet("color: rgba(214, 213, 225, 1);"
                                 "font: bold Arial;"
                                 "font-size: 15px;");
    search_textbox = new CustomLineEdit;
    search_button = new CustomButton("Search");

    payment_textbox = new CustomLineEdit;
    payment_textbox->setReadOnly(true);
    search_details->addWidget(new CustomLabel("Current payment:"), 0, 0);
    search_details->addWidget(payment_textbox, 0, 1);
    payment_textbox->setText("$" + QString::number(service.getPayment()));

    search_details->addWidget(new CustomLabel("Selected size:"), 1, 0);
    search_details->addWidget(search_textbox, 1, 1);
    search_details->addWidget(search_button, 2, 0, 1, 2);

    search_groupbox->setLayout(search_details);
    main_layout->addWidget(search_groupbox);

    main_layout->addLayout(options);
    displayMenuConnect();
}

void GuiUserWindow::shoppingBasket() {
    table = new QTableWidget;
    populateTable(false, service.getShoppingBasket());
    main_layout->addWidget(table);

    back_button = new CustomButton("Back");
    main_layout->addWidget(back_button);
    QObject::connect(back_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        mainMenu();
    });
}

void GuiUserWindow::show() {

}

void GuiUserWindow::mainMenuConnect() {
    QObject::connect(display_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        display();
    });
    QObject::connect(basket_button, &QPushButton::clicked, [&](){
        auto data = service.getShoppingBasket();
        if (!data.size()) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "There are no trench coats in the shopping basket!");
            messagebox.exec();
            return;
        }
        clearLayout(main_layout);
        shoppingBasket();
    });
    QObject::connect(show_button, &QPushButton::clicked, [&](){
        auto data = service.getShoppingBasket();
        if (!data.size()) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "There are no trench coats in the shopping basket!");
            messagebox.exec();
            return;
        }
        service.showShoppingBasket();
//        emit launchCSV();
    });
    QObject::connect(switch_button, &QPushButton::clicked, [&](){
        emit userSwitch();
    });
    QObject::connect(exit_button, &QPushButton::clicked, [&](){
        close();
    });
}

void GuiUserWindow::displayMenuConnect() {
    QObject::connect(search_button, &QPushButton::clicked, [&](){
        searched_size = search_textbox->text().toStdString();
        int length = service.getCoatsPerSizeLength(searched_size);

        if (!length) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "No trench coats were found!");
            messagebox.exec();
        }

        searching = 0;

        service.launchBrowserSizeCoatPhoto(searching, searched_size);
        auto coat = service.filterDataPerSize(searched_size)[searching];
        size_textbox->setText(QString::fromStdString(coat.getSize()));
        colour_textbox->setText(QString::fromStdString(coat.getColour()));
        price_textbox->setText(QString::number(coat.getPrice()));
        quantity_textbox->setText(QString::number(coat.getQuantity()));
        link_textbox->setText(QString::fromStdString(coat.getPhotograph()));
    });
    QObject::connect(add_button, &QPushButton::clicked, [&](){
        if (searching == -1) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "A search has not started yet!");
            messagebox.exec();
            return;
        }
        service.addToShoppingBasket(searching, searched_size);
        payment_textbox->setText("$" + QString::number(service.getPayment()));
        skip_button->click();
    });
    QObject::connect(skip_button, &QPushButton::clicked, [&](){
        if (searching == -1) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "A search has not started yet!");
            messagebox.exec();
            return;
        }

        int length = service.getCoatsPerSizeLength(searched_size);
        searching++;
        if (searching >= length) searching = 0;

        service.launchBrowserSizeCoatPhoto(searching, searched_size);
        auto coat = service.filterDataPerSize(searched_size)[searching];
        size_textbox->setText(QString::fromStdString(coat.getSize()));
        colour_textbox->setText(QString::fromStdString(coat.getColour()));
        price_textbox->setText(QString::number(coat.getPrice()));
        quantity_textbox->setText(QString::number(coat.getQuantity()));
        link_textbox->setText(QString::fromStdString(coat.getPhotograph()));
    });
    QObject::connect(stop_button, &QPushButton::clicked, [&](){
        if (searching == -1) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "A search has not started yet!");
            messagebox.exec();
            return;
        }
        searching = -1;
        size_textbox->clear();
        colour_textbox->clear();
        price_textbox->clear();
        quantity_textbox->clear();
        link_textbox->clear();
        search_textbox->clear();
    });
    QObject::connect(back_button, &QPushButton::clicked, [&](){
        clearLayout(main_layout);
        mainMenu();
    });
}

void GuiUserWindow::populateTable(bool from_service, std::vector<TrenchCoat> data) {
    size_t columns = 5, rows = service.getLength();
    if (!from_service) rows = data.size();

    table->horizontalHeader()->setStretchLastSection(true);
    if (from_service)
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->hide();

    table->setStyleSheet("background-color: transparent;"
                         "color: rgba(214, 213, 225, 1);"
                         "font: bold Arial;"
                         "font-size: 15px;");
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: rgba(45, 45, 45, 45)}; ");

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

    for (size_t i = 0; i < rows; ++i) {
        QTableWidgetItem* item = table->verticalHeaderItem(i);
        item->setText(QString::number(i + 1));
    }

    if (from_service) data = service.getData();
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
