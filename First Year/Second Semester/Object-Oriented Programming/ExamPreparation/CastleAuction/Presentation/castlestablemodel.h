#ifndef CASTLESTABLEMODEL_H
#define CASTLESTABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include <Controller/subjectcontroller.h>

class CastlesTableModel : public QAbstractTableModel
{
private:
    SubjectController& service;
public:
    explicit CastlesTableModel(SubjectController& service, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // CASTLESTABLEMODEL_H
