#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ObserverWindow.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->verticalLayout);
    resize(550, 370);

    model = new CastlesTableModel {service};
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int bidders = ui->lineEdit->text().toInt();
    ui->lineEdit->setReadOnly(true);

    for (int i = 0; i < bidders; ++i)
    {
        ObserverWindow* newObserver = new ObserverWindow {service};
        QObject::connect(newObserver, &ObserverWindow::newBidSignal, this, [&](){
            emit model->layoutChanged();
        });

        newObserver->show();
    }
}

