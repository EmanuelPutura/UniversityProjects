#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->verticalLayout);

    data.push_back("Aurel Mircea Badea");
    data.push_back("Aurel Mihaitza Pustiu");
    data.push_back("Vijelie Mircea Vali");
    data.push_back("Guta Ioan Becali");
    data.push_back("Obama Mircea Giovanni");

    model = new ListModel {data};
//    ui->listView->setModel(model);

    proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);
    ui->listView->setModel(proxy);

    proxy->sort(0, Qt::DescendingOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

