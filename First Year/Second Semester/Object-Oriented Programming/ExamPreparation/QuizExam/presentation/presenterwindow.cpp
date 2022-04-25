#include "participantwindow.h"
#include "presenterwindow.h"
#include "ui_presenterwindow.h"

#include <QDebug>
#include <QMessageBox>

#include <exceptions/exception.h>

PresenterWindow::PresenterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresenterWindow), participants_repo {"../QuizExam/files/participants.txt"}, questions_repo {"../QuizExam/files/questions.txt"}
{
    ui->setupUi(this);
    setWindowTitle("Presenter");
    setLayout(ui->verticalLayout);

    presenter_model = new PresenterTableModel {questions_repo};
    presenter_proxy = new CustomProxyModel(true);
    presenter_proxy->setSourceModel(presenter_model);
    ui->tableView->setModel(presenter_proxy);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);

    presenter_proxy->sort(0);

//    participant_model = new ParticipantTableModel {questions_repo};
//    participant_proxy = new CustomProxyModel(false);
//    participant_proxy->setSourceModel(participant_model);
//    participant_proxy->sort(2, Qt::DescendingOrder);

    for (const auto& p : participants_repo.data()) {
        auto pm = new ParticipantTableModel {questions_repo};
        auto pp = new CustomProxyModel(false);
        pp->setSourceModel(pm);
        pp->sort(2, Qt::DescendingOrder);

//        models.push_back({pm, pp});

        auto w = new ParticipantWindow {*this, p, pp, pm};
        w->show();
        addObserver(w);
    }
}

PresenterWindow::~PresenterWindow()
{
    delete ui;
}

void PresenterWindow::on_pushButton_clicked()
{
    auto id = ui->lineEdit->text().toInt();
    auto text = ui->lineEdit_2->text().toStdString();
    auto correct = ui->lineEdit_3->text().toStdString();
    auto score = ui->lineEdit_4->text().toInt();

    if (text == "") {
        QMessageBox messagebox(QMessageBox::Critical, "Error", "Invalid text!");
        messagebox.exec();
        return;
    }

    for (const auto& q : questions_repo.data())
        if (q.getID() == id) {
            QMessageBox messagebox(QMessageBox::Critical, "Error", "Invalid ID!");
            messagebox.exec();
            return;
        }

    Question q {id, text, correct, score};
    questions_repo.add(q);
    presenter_proxy->insertRow(presenter_proxy->rowCount());
    notifyAll();
    presenter_proxy->sort(0);
}

