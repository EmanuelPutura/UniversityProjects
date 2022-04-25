#include "controller.h"

#include <QDebug>

#include <presentation/writerwindow.h>

#include "exception.h"

Controller::Controller() : writers {"../ScreenWriting/files/writers.txt"}, ideas {"../ScreenWriting/files/ideas.txt"}
{
    model = new TableModel {ideas};
    proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);

    auto data = writers.data();
    for (int i = 0; i < writers.size(); ++i) {
        auto w = new WriterWindow {*this, data[i], proxy};
        w->show();
        addObserver(w);
    }
}

void Controller::add(const Idea &idea)
{
    if (idea.getDescription() == "" || idea.getAct() < 1 || idea.getAct() > 3)
        throw Exception("Invalid idea!");

    for (const auto& i : ideas.data()) {
        if (i.getDescription() == idea.getDescription() && i.getAct() == idea.getAct())
            throw Exception("Invalid idea!");
    }

    ideas.add(idea);
    proxy->insertRow(proxy->rowCount());
    notifyAll();
}

void Controller::remove(int row, const Idea &idea)
{
    int i = 0;
    for (const auto& el : ideas.data()) {
        if (el.getDescription() == idea.getDescription()) {
            break;
        }
        i++;
    }

    auto index1 = model->index(i, 0);
    auto index2 = proxy->mapFromSource(index1);

//    qDebug() << index1.row() << index2.row();

    ideas.remove(idea);
    proxy->removeRow(row);
    notifyAll();
}

void Controller::updateBtn(bool flag)
{
    for (const auto& o : observers)
        o->updateBtn(flag);
}

void Controller::updateIdea(const Idea &id1, const Idea &id2)
{
    ideas.update(id1, id2);
    emit proxy->layoutChanged();
    notifyAll();
}
