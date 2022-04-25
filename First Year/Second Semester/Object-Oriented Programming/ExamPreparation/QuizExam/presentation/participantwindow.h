#ifndef PARTICIPANTWINDOW_H
#define PARTICIPANTWINDOW_H

#include "customproxymodel.h"
#include "participanttablemodel.h"
#include "presenterwindow.h"

#include <QSortFilterProxyModel>
#include <QWidget>

#include <domain/observerpattern.h>
#include <domain/participant.h>

namespace Ui {
class ParticipantWindow;
}

class ParticipantWindow : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit ParticipantWindow(PresenterWindow& presenter, Participant participant, CustomProxyModel *proxy_model, ParticipantTableModel *model, QWidget *parent = nullptr);
    ~ParticipantWindow();

    void update() override;
    void updateBtn(bool flag) override;
private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::ParticipantWindow *ui;
    Participant participant;
    PresenterWindow& presenter;

    CustomProxyModel *proxy_model;
    ParticipantTableModel *model;
    std::vector<int> answered;
};

#endif // PARTICIPANTWINDOW_H
