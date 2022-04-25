#include "observerwindow.h"
#include "ui_observerwindow.h"

#include <QDebug>

void ObserverWindow::initCheckBoxes()
{
    auto castles = service.getRepoData();
    for (const auto& el : castles) {
        QCheckBox* checkbox = new QCheckBox(QString::fromStdString(el.getName()));
        checkboxes.push_back(checkbox);
        ui->verticalLayout->addWidget(checkbox);

        QObject::connect(checkbox, &QCheckBox::stateChanged, this, [&](){
            auto sender = (QCheckBox*)QObject::sender();
            bool state = (sender->checkState() == Qt::Checked);
            service.notifyCheckBox(sender->text().toStdString(), state);

            if (state)
                service.addFilteredData(sender->text().toStdString());
            else service.removeFilteredData(sender->text().toStdString());
        });
    }
}

ObserverWindow::ObserverWindow(SubjectController &service, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObserverWindow),
    service (service)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    service.addObserver(this);

    model = new CastlesTableModel {service};
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();

    initCheckBoxes();
}

void ObserverWindow::update()
{
    emit model->layoutChanged();
    emit newBidSignal();
}

void ObserverWindow::updateCheckBox(std::string castle, bool value)
{
    int index = 0;
    for (const auto& el : service.getRepoData())
    {
        if (el.getName() == castle)
            break;
        index++;
    }

    if (index < 0 || index >= service.getRepoLength()) return;
    checkboxes[index]->setChecked(value);
}

ObserverWindow::~ObserverWindow()
{
    delete ui;
}

void ObserverWindow::on_pushButton_2_clicked()
{
    auto data = service.getRepoData();
    for (int i = 0; i < data.size(); ++i) {
        if (checkboxes[i]->isChecked()) {
            service.updateCurrentPrice(i, data[i].getCurrentPrice() + 10);
        }
    }
    emit newBidSignal();
}

void ObserverWindow::on_pushButton_clicked()
{
    auto data = service.getRepoData();
    for (int i = 0; i < data.size(); ++i) {
        if (checkboxes[i]->isChecked()) {
            service.updateCurrentPrice(i, data[i].getCurrentPrice() + 100);
        }
    }
    emit newBidSignal();
}

