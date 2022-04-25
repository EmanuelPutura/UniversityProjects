#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <string>

class ListModel : public QAbstractListModel
{
private:
    std::vector<std::string>& elems;
public:
    explicit ListModel(std::vector<std::string>& elems, QObject *parent = nullptr);

    // number of rows
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // data at a given (row, column) table position
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // LISTMODEL_H
