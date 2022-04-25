#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <domain/observerpattern.h>

#include <infrastructure/idearepo.h>
#include <infrastructure/writerrepo.h>

#include <QSortFilterProxyModel>

#include "presentation/tablemodel.h"

class Controller : public Subject
{
private:
    WriterRepository writers;
    IdeaRepository ideas;

    TableModel *model;
    QSortFilterProxyModel *proxy;
public:
    Controller();

    void add(const Idea& idea);
    void remove(int row, const Idea& idea);
    void updateBtn(bool flag);
    void updateIdea(const Idea& id1, const Idea& id2);

    inline const std::vector<Idea>& getIdeas() const { return ideas.data(); }
};

#endif // CONTROLLER_H
