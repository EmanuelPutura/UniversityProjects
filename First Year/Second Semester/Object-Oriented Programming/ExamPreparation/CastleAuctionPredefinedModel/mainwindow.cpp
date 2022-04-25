#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegExp>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MainWindow), repository("../CastleAuctionPredefinedModel/files/castles.txt")
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    custom_model = new CastlesModel {repository};
    proxy_model = new QSortFilterProxyModel;
    proxy_model->setSourceModel(custom_model);

    ui->tableView->setModel(proxy_model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);

//    painter = new QPainter(this);
//    flayout = new QFormLayout(this);
//    flayout->setSizeConstraint(QLayout::SetMinimumSize);

    layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    ui->verticalLayout->addLayout(layout);
//    ui->verticalLayout->addLayout(flayout);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    auto idx = ui->tableView->model()->index(index.row(), 0);
    ui->lineEdit_2->setText(ui->tableView->model()->data(idx).toString());

    idx = ui->tableView->model()->index(index.row(), 1);
    ui->lineEdit_3->setText(ui->tableView->model()->data(idx).toString());

    idx = ui->tableView->model()->index(index.row(), 2);
    ui->lineEdit_4->setText(ui->tableView->model()->data(idx).toString());

    idx = ui->tableView->model()->index(index.row(), 3);
    ui->lineEdit_5->setText(ui->tableView->model()->data(idx).toString());
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxy_model->setFilterRegExp(QRegExp(ui->lineEdit->text(), Qt::CaseInsensitive, QRegExp::FixedString));
}

void MainWindow::on_pushButton_clicked()
{
    CircleWidget *cw = new CircleWidget(ui->lineEdit_6->text().toInt() * 5);
    circles.push_back({cw, new QLabel("Circle no. " + QString::number(circles.size() + 1))});

    int idx = circles.size() - 1;
//    flayout->addRow(circles[idx].second, circles[idx].first);
    layout->addWidget(circles[idx].second, idx, 0);
    layout->addWidget(circles[idx].first, idx, 1);
}

