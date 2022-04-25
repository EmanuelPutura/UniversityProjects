#include "CustomButton.h"

#include <presentation/GuiOptionWindow.h>

#include <QPainter>
#include <QRect>
#include <QVBoxLayout>

GuiOptionWindow::GuiOptionWindow(QWidget *parent) : QWidget(parent) {
    initWindow();
    connect();
}

GuiOptionWindow::~GuiOptionWindow() {
}

void GuiOptionWindow::closeEvent(QCloseEvent *event) {
    flag = -1;
    emit flagChange();
    QWidget::closeEvent(event);
}

void GuiOptionWindow::initWindow() {
    this->setWindowTitle("TrenchCoats Manager");
    this->resize(500, 250);

    QVBoxLayout* main_layout = new QVBoxLayout(this);

    admin_button = new CustomButton("Admin");
    main_layout->addWidget(admin_button);

    user_button = new CustomButton("User");
    main_layout->addWidget(user_button);

    change_button = new CustomButton("Change");
    main_layout->addWidget(change_button);

    exit_button = new CustomButton("Exit");
    main_layout->addWidget(exit_button);
}

void GuiOptionWindow::connect() {
    QObject::connect(admin_button, &QPushButton::clicked, [&](){
        flag = 1;
        emit flagChange();
    });
    QObject::connect(user_button, &QPushButton::clicked, [&](){
        flag = 2;
        emit flagChange();
    });
    QObject::connect(change_button, &QPushButton::clicked, [&](){
        basket_type = basket_type == 0 ? 1 : 0;
    });
    QObject::connect(exit_button, &QPushButton::clicked, [&](){
        flag = -1;
        emit flagChange();
    });
}

void GuiOptionWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QRect rectangle = event->rect();
    QPainter painter(this);
    QGradient gradient(QGradient::MidnightBloom);
    painter.fillRect(rectangle, gradient);
}
