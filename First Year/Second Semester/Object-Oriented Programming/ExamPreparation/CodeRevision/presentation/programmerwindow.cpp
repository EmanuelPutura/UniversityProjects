#include "programmerwindow.h"
#include "ui_programmerwindow.h"

#include <QMessageBox>

ProgrammerWindow::ProgrammerWindow(Programmer programmer, Controller &controller, QSortFilterProxyModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgrammerWindow), programmer(programmer), model(model), controller(controller)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(programmer.getName()));

//    proxy_model = new QSortFilterProxyModel;
//    proxy_model->setSourceModel(model);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);

    model->sort(0, Qt::AscendingOrder);

    QString revised = QString::number(programmer.getRevisedFiles());
    QString to_revise = QString::number(programmer.getToRevise());
    ui->label->setText("Revised: " + revised);
    ui->label_2->setText("Still to be revised: " + to_revise);
}

ProgrammerWindow::~ProgrammerWindow()
{
    delete ui;
}

void ProgrammerWindow::update()
{
    emit model->layoutChanged();
}

void ProgrammerWindow::buttonUpdate(bool flag)
{
    ui->pushButton_2->setEnabled(flag);
}

void ProgrammerWindow::on_pushButton_clicked()
{
    std::string str1 = ui->lineEdit->text().toStdString();
    std::string str2 = programmer.getName();
    int ret = controller.add(str1, str2);
    if (ret == -1) {
        QMessageBox messagebox(QMessageBox::Critical, "Error", "Invalid file name!");
        messagebox.exec();
        return;
    }
}


void ProgrammerWindow::on_pushButton_2_clicked()
{
    auto idx = ui->tableView->selectionModel()->selectedIndexes().at(0);
    auto sidx = ui->tableView->model()->index(idx.row(), 0);
    auto name = ui->tableView->model()->data(sidx);
    sidx = ui->tableView->model()->index(idx.row(), 2);
    auto creator = ui->tableView->model()->data(sidx);

    SourceFile s1(name.toString().toStdString(), "", "", "");
    SourceFile s2(name.toString().toStdString(), "revised", creator.toString().toStdString(), programmer.getName());

    controller.updateSourceFile(s1, s2);

    programmer.decToRevised();
    programmer.incRevisedFiles();
    controller.updateProgrammer(programmer, programmer);

    QString revised = QString::number(programmer.getRevisedFiles());
    QString to_revise = QString::number(programmer.getToRevise());
    ui->label->setText("Revised: " + revised);
    ui->label_2->setText("Still to be revised: " + to_revise);
    if (to_revise.toInt() == 0) {
        QMessageBox messagebox(QMessageBox::Information, "Congratulations", "Congratulations!");
        messagebox.exec();
    }

    controller.notifyButton(false);
    ui->pushButton_2->setEnabled(false);
}


void ProgrammerWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    auto idx = ui->tableView->model()->index(row, 1);
    auto status = ui->tableView->model()->data(idx);
    idx = ui->tableView->model()->index(index.row(), 2);
    auto creator = ui->tableView->model()->data(idx);
    idx = ui->tableView->model()->index(index.row(), 0);
    auto name = ui->tableView->model()->data(idx).toString();
    selected = name.toStdString();

    if (status == "not_revised" && creator != QString::fromStdString(programmer.getName())) {
        ui->pushButton_2->setEnabled(true);
        controller.notifyButton(true);
    }
    else
    {
        controller.notifyButton(false);
        ui->pushButton_2->setEnabled(false);
    }
}

