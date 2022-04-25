#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <domain/observerpattern.h>

#include <infrastructure/idearepo.h>
#include <infrastructure/writerrepo.h>

#include <QSortFilterProxyModel>

class Service : public Subject
{
private:
    WriterRepository writers;
    IdeaRepository ideas;
public:
    Service();
};

#endif // CONTROLLER_H
