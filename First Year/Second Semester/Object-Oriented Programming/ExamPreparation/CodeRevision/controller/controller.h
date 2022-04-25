#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <domain/observerpattern.h>

#include <infrastructure/programmerrepo.h>
#include <infrastructure/sourcefilerepo.h>

#include <presentation/sourcestablemodel.h>

#include <QSortFilterProxyModel>



class Controller : Subject
{
private:
    ProgrammerRepo programmers_repo;
    SourceFileRepo sources_repo;
    SourcesTableModel *model;
    QSortFilterProxyModel *proxy_model;
public:
    Controller();

    int add(std::string name, std::string programmer);
    void updateSourceFile(const SourceFile& old, const SourceFile& n);
    void updateProgrammer(const Programmer& old, const Programmer& n);

    inline const std::vector<SourceFile>& sourcesData() const { return sources_repo.data(); }
    inline const std::vector<Programmer>& programmersData() const { return programmers_repo.data(); }

    void notifyButton(bool flaf);
};

#endif // CONTROLLER_H
