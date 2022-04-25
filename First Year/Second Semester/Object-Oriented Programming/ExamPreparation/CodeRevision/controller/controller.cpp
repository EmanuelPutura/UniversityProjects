#include "controller.h"
#include <QDebug>

#include <presentation/programmerwindow.h>
#include <presentation/statisticswindow.h>


int Controller::add(std::string name, std::string programmer)
{
    if (name == "") return -1;
    auto data = sources_repo.data();
    for (const auto& el : data)
        if (el.getName() == name)
            return -1;
    SourceFile file {name, "not_revised", programmer, ""};
    sources_repo.add(file);
    notifyAll();
    return 0;
}

void Controller::updateSourceFile(const SourceFile &old, const SourceFile &n)
{
    sources_repo.update(old, n);
    notifyAll();
}

void Controller::updateProgrammer(const Programmer &old, const Programmer &n)
{
    programmers_repo.update(old, n);
    notifyAll();
}

void Controller::notifyButton(bool flag)
{
    for (const auto& obs : observers)
        obs->buttonUpdate(flag);
}

Controller::Controller() : Subject(), programmers_repo {"../CodeRevision/files/programmers.txt"}, sources_repo {"../CodeRevision/files/sources.txt"}
{
    model = new SourcesTableModel(sources_repo);
    proxy_model = new QSortFilterProxyModel;
    proxy_model->setSourceModel(model);

    int size = programmers_repo.size();
    auto data = programmers_repo.data();

    for (int i = 0; i < size; ++i) {
        auto w = new ProgrammerWindow {data[i], *this, proxy_model};
        w->show();
        addObserver(w);
    }

    auto w = new StatisticsWindow(*this);
    w->show();
    addObserver(w);
    w->update();
}
