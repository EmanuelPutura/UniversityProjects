#include "participantwindow.h"
#include "ui_participantwindow.h"

#include <QDebug>

ParticipantWindow::ParticipantWindow(PresenterWindow &presenter, Participant participant, CustomProxyModel *proxy_model, ParticipantTableModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParticipantWindow), participant(participant), proxy_model(proxy_model), model(model), presenter(presenter)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(participant.getName()));

    ui->tableView->setModel(proxy_model);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);
}

ParticipantWindow::~ParticipantWindow()
{
    delete ui;
}

void ParticipantWindow::update()
{
    proxy_model->insertRow(proxy_model->rowCount());
    proxy_model->sort(2, Qt::DescendingOrder);
}

void ParticipantWindow::updateBtn(bool flag)
{

}

void ParticipantWindow::on_pushButton_clicked()
{
    auto index = ui->tableView->selectionModel()->selectedIndexes().at(0);
    auto idx = ui->tableView->model()->index(index.row(), 0);
    auto id = ui->tableView->model()->data(idx).toInt();
    model->addAnswer(id);
    emit proxy_model->layoutChanged();
    ui->pushButton->setEnabled(false);

    idx = ui->tableView->model()->index(index.row(), 2);
    auto score = ui->tableView->model()->data(idx).toInt();

    auto answer = ui->lineEdit->text().toStdString();
    auto data = presenter.getQuestions();

    bool found = false;
    for (const auto& q : data) {
        if (q.getID() == id && q.getCorrect() != answer) break;
        if (q.getCorrect() == answer && q.getID() == id) {
            found = true;
            break;
        }
    }

    if (found) {
        auto current = ui->lineEdit_2->text().toInt();
        current += score;
        qDebug() << current;
        ui->lineEdit_2->setText(QString::number(current));
    }
}


void ParticipantWindow::on_tableView_clicked(const QModelIndex &index)
{
    auto idx = ui->tableView->model()->index(index.row(), 0);
    auto id = ui->tableView->model()->data(idx).toInt();

    if (model->isAnswered(id))
        ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}

