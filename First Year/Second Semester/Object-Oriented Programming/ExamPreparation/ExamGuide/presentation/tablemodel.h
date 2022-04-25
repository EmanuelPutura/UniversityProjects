#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <infrastructure/issuerepository.h>
#include <infrastructure/userrepository.h>


class TableModel : public QAbstractTableModel
{
private:
    IssueRepository& repository;
public:
    TableModel(IssueRepository &repository, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // TABLEMODEL_H
