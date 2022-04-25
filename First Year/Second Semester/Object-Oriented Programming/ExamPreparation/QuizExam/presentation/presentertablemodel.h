#ifndef PRESENTERTABLEMODEL_H
#define PRESENTERTABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

#include <infrastructure/questions_repo.h>

class PresenterTableModel : public QAbstractTableModel
{
private:
    QuestionsRepository& repository;
public:
    explicit PresenterTableModel(QuestionsRepository &repository, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // number of columns
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool insertRows(int position, int rows, const QModelIndex& parent) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
};

#endif // PRESENTERTABLEMODEL_H
