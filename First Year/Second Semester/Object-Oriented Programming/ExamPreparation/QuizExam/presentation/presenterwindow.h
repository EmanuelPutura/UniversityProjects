#ifndef PRESENTERWINDOW_H
#define PRESENTERWINDOW_H

#include <QSortFilterProxyModel>
#include <QWidget>

#include <infrastructure/participant_repo.h>

#include <domain/observerpattern.h>

#include "infrastructure/questions_repo.h"

#include "customproxymodel.h"
#include "participanttablemodel.h"
#include "presentertablemodel.h"

namespace Ui {
class PresenterWindow;
}

class PresenterWindow : public QWidget, public Subject
{
    Q_OBJECT

public:
    explicit PresenterWindow(QWidget *parent = nullptr);
    ~PresenterWindow();


    inline const std::vector<Question>& getQuestions() const { return questions_repo.data(); }
private slots:
    void on_pushButton_clicked();

private:
    Ui::PresenterWindow *ui;
    ParticipantsRepository participants_repo;
    QuestionsRepository questions_repo;

    PresenterTableModel *presenter_model;
    CustomProxyModel *presenter_proxy;

    ParticipantTableModel *participant_model;
    CustomProxyModel *participant_proxy;
};

#endif // PRESENTERWINDOW_H
