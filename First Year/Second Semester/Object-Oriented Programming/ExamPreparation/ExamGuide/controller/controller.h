#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <infrastructure/issuerepository.h>
#include <infrastructure/userrepository.h>

#include <domain/observerpattern.h>

#include <presentation/tablemodel.h>

#include <QSortFilterProxyModel>


class Controller : Subject
{
private:
    IssueRepository issue_repo;
    UserRepository user_repo;

    TableModel *model;
    QSortFilterProxyModel *proxy_model;
public:
    Controller();

    int addIssue(const Issue& is);
    void removeIssue(const Issue& is);
    void updateIssue(const Issue& old, const Issue& obj);

    void notifyBtn(bool flag);

    inline const std::vector<Issue>& issueData() const { return issue_repo.data(); }
    inline const std::vector<User>& userData() const { return user_repo.data(); }
};

#endif // CONTROLLER_H
