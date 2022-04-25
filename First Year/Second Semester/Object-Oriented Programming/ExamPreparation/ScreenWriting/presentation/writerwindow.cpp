#include "writerwindow.h"
#include "ui_writerwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include "exception.h"
#include <fstream>
#include <iostream>
#include <sstream>

WriterWindow::WriterWindow(Controller &controller, Writer writer, QSortFilterProxyModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriterWindow), controller(controller), writer(writer), model(model)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    setWindowTitle(QString::fromStdString(writer.getName()) + " - " + QString::fromStdString(writer.getExpertise()));

    layout = new QVBoxLayout;

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);

    ui->tableView->setModel(model);
    model->sort(3);

    if (writer.getExpertise() == "Senior")
        ui->pushButton_2->setEnabled(true);

    if (computeAccepted() > 0)
        ui->pushButton_3->setEnabled(true);
    else ui->pushButton_3->setEnabled(false);
}

void WriterWindow::update()
{
    if (computeAccepted() > 0)
        ui->pushButton_3->setEnabled(true);
    else ui->pushButton_3->setEnabled(false);
    model->sort(3);
}

void WriterWindow::updateBtn(bool flag)
{
    if (writer.getExpertise() != "Senior")
        return;

    ui->pushButton_2->setEnabled(flag);
}

int WriterWindow::computeAccepted() const
{
    int cnt = 0;
    for (const auto& id : controller.getIdeas()) {
        if (id.getCreator() == writer.getName() && id.getStatus() == "accepted")
            cnt++;
    }
    return cnt;
}

WriterWindow::~WriterWindow()
{
    delete ui;
}

void WriterWindow::on_pushButton_clicked()
{
    auto descr = ui->lineEdit->text().toStdString();
    auto act = ui->lineEdit_2->text().toInt();

    Idea idea {descr, "proposed", writer.getName(), act};
    try {
        controller.add(idea);
    }
    catch (Exception& ex) {
        QMessageBox messagebox(QMessageBox::Critical, "Error", QString::fromStdString(ex.getMessage()));
        messagebox.exec();
        return;
    }
}


void WriterWindow::on_pushButton_2_clicked()
{
    if (writer.getExpertise() != "Senior")
        return;

    auto index = ui->tableView->selectionModel()->selectedIndexes().at(0);
    index = ui->tableView->model()->index(index.row(), 0);
    auto descr = ui->tableView->model()->data(index).toString().toStdString();
    index = ui->tableView->model()->index(index.row(), 1);
    auto status = ui->tableView->model()->data(index).toString().toStdString();
    index = ui->tableView->model()->index(index.row(), 2);
    auto creator = ui->tableView->model()->data(index).toString().toStdString();
    index = ui->tableView->model()->index(index.row(), 3);
    auto act = ui->tableView->model()->data(index).toInt();

    Idea idea {descr, "accepted", creator, act};
    controller.updateIdea(idea, idea);

    if (computeAccepted() > 0)
        ui->pushButton_3->setEnabled(true);
    else ui->pushButton_3->setEnabled(false);
}


void WriterWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (writer.getExpertise() != "Senior")
        return;

    auto idx = ui->tableView->model()->index(index.row(), 1);
    auto status = ui->tableView->model()->data(idx);

    bool flag;
    if (status == "proposed") {
        ui->pushButton_2->setEnabled(true);
        flag = true;
    }
    else {
        ui->pushButton_2->setEnabled(false);
        flag = false;
    }
    controller.updateBtn(flag);
}


void WriterWindow::on_pushButton_3_clicked()
{
    auto ideas = controller.getIdeas();
    delete layout;
    layout = new QVBoxLayout;
    ui->verticalLayout->addLayout(layout);

    edits.clear();
    for (const auto& i : ideas) {
        if (i.getCreator() == writer.getName() && i.getStatus() == "accepted") {
            auto txt = new QTextEdit(QString::fromStdString(i.getDescription()));
            layout->addWidget(txt);

            auto save_btn = new QPushButton("Save");
            layout->addWidget(save_btn);

            edits.push_back({txt, save_btn});

            QObject::connect(save_btn, &QPushButton::clicked, this, [txt](){
                QString file = QFileDialog::getSaveFileName();
                qDebug() << file;

                std::ofstream fout (file.toStdString());
                if (fout.is_open()) {
                    std::stringstream stream(txt->toPlainText().toStdString());
                    std::string token;
                    while (getline(stream, token)) {
                        fout << token << '\n';
                    }
                    fout.close();
                }
            });
        }
    }
}


void WriterWindow::on_pushButton_4_clicked()
{
    QString file = QFileDialog::getSaveFileName();

    std::ofstream fout(file.toStdString());

    if (fout.is_open()) {
        fout << "Act 1\n";
        for (const auto& id : controller.getIdeas()) {
            if (id.getAct() == 1 && id.getStatus() == "accepted") {
                fout << id.getDescription() << " (" << id.getCreator() << ")\n";
            }
        }

        fout << "Act 2\n";
        for (const auto& id : controller.getIdeas()) {
            if (id.getAct() == 2 && id.getStatus() == "accepted") {
                fout << id.getDescription() << " (" << id.getCreator() << ")\n";
            }
        }

        fout << "Act 3\n";
        for (const auto& id : controller.getIdeas()) {
            if (id.getAct() == 3 && id.getStatus() == "accepted") {
                fout << id.getDescription() << " (" << id.getCreator() << ")\n";
            }
        }

        fout.close();
    }
}


void WriterWindow::on_pushButton_5_clicked()
{
    auto index1 = ui->tableView->selectionModel()->selectedIndexes().at(0);
    auto index2 = ui->tableView->model()->index(index1.row(), 0);

//    qDebug() << index1.row() << index2.row();

    auto descr = ui->tableView->model()->data(index2).toString().toStdString();
    controller.remove(index2.row(), Idea{descr, "", "", 0});
}

