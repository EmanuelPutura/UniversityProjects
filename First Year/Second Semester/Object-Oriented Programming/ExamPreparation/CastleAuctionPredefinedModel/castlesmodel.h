#ifndef CASTLESMODEL_H
#define CASTLESMODEL_H

#include <QSortFilterProxyModel>

#include <infrastructure/repository.h>

class CastlesModel : public QAbstractTableModel
{
private:
    Repository& repository;
public:
    explicit CastlesModel(Repository& repository, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // CASTLESMODEL_H
