#ifndef SOURCESTABLEMODEL_H
#define SOURCESTABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <infrastructure/sourcefilerepo.h>


class SourcesTableModel : public QAbstractTableModel
{
private:
    SourceFileRepo& sources;
public:
    SourcesTableModel(SourceFileRepo& sources, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // SOURCESTABLEMODEL_H
