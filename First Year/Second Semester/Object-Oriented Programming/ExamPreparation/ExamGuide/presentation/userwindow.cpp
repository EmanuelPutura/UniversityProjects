#include "userwindow.h"
#include "ui_userwindow.h"

#include <QMessageBox>
#include <QDebug>

UserWindow::UserWindow(Controller &controller, User user, QSortFilterProxyModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow), controller(controller), user(user), model(model)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);

    setWindowTitle(QString::fromStdString(user.getName()) + " - " + QString::fromStdString(user.getType()));

    if (user.getType() == "programmer") {
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
    }
    else
        ui->pushButton_3->setEnabled(false);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);

    model->sort(0, Qt::AscendingOrder);
    model->sort(1, Qt::AscendingOrder);
}

void UserWindow::update()
{
    emit model->layoutChanged();
    model->sort(0, Qt::AscendingOrder);
    model->sort(1, Qt::AscendingOrder);
}

void UserWindow::updateBtn(bool flag)
{
    if (user.getType() == "programmer")
        ui->pushButton_3->setEnabled(flag);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    auto description = ui->lineEdit->text().toStdString();
    Issue is {description, "open", user.getName(), ""};
    if (controller.addIssue(is) == -1)
    {
        QMessageBox messagebox(QMessageBox::Critical, "Error", "Invalid issue!");
        messagebox.exec();
        return;
    }
}


void UserWindow::on_pushButton_2_clicked()
{
    auto description = ui->lineEdit_2->text().toStdString();
    for (const auto& i : controller.issueData()) {
        if (i.getDescription() == description) {
            if (i.getStatus() == "open") {
                QMessageBox messagebox(QMessageBox::Critical, "Error", "Cannot remove issue!");
                messagebox.exec();
                return;
            }
            controller.removeIssue(i);
        }
    }
}


void UserWindow::on_tableView_clicked(const QModelIndex &index)
{
    auto idx = ui->tableView->model()->index(index.row(), 1);
    auto status = ui->tableView->model()->data(idx);
    if (status == "open" && user.getType() == "programmer") {
        controller.notifyBtn(true);
    }
    else if (user.getType() == "programmer"){
        controller.notifyBtn(false);
    }
}


void UserWindow::on_pushButton_3_clicked()
{
    auto index = ui->tableView->selectionModel()->selectedIndexes().at(0);
    auto idx = ui->tableView->model()->index(index.row(), 0);

    auto name = user.getName();
    auto description = ui->tableView->model()->data(idx).toString().toStdString();

    idx = ui->tableView->model()->index(index.row(), 0);
    auto reporter = ui->tableView->model()->data(idx).toString().toStdString();

    Issue old {description, "", "", ""};
    Issue obj {description, "closed", reporter, name};
    controller.updateIssue(old, obj);
}

