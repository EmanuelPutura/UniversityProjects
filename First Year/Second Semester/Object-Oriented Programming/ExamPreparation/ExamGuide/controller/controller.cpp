#include "controller.h"

#include <QDebug>
#include <algorithm>

#include <presentation/statisticswindow.h>
#include <presentation/userwindow.h>

Controller::Controller() : Subject(), user_repo("../ExamGuide/files/users.txt"), issue_repo("../ExamGuide/files/issues.txt")
{
    model = new TableModel {issue_repo};
    proxy_model = new QSortFilterProxyModel;
    proxy_model->setSourceModel(model);

    auto users = user_repo.data();
    for (const auto& u : users) {
        auto w = new UserWindow {*this, u, proxy_model};
        w->show();
        addObserver(w);
    }

    auto w = new StatisticsWindow {*this};
    w->show();
    addObserver(w);
    w->update();
}

int Controller::addIssue(const Issue &is)
{
    if (is.getDescription() == "")
        return -1;

    auto issues = issue_repo.data();
    auto it = std::find_if(issues.begin(), issues.end(), [&is](const auto& el){
        return is.getDescription() == el.getDescription();
    });

    if (it != issues.end())
        return -1;

    issue_repo.add(is);
    notifyAll();
    return 0;
}

void Controller::removeIssue(const Issue &is)
{
    issue_repo.remove(is);
    notifyAll();
}

void Controller::updateIssue(const Issue &old, const Issue &obj)
{
    issue_repo.update(old, obj);
    notifyAll();
}

void Controller::notifyBtn(bool flag)
{
    for (const auto& o : observers)
        o->updateBtn(flag);
}
