#include "listmodel.h"

ListModel::ListModel(std::vector<std::string> &elems, QObject *parent) : elems(elems), QAbstractListModel(parent)
{

}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return elems.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    auto obj = elems[index.row()];
    if (role == Qt::DisplayRole)
        return QString::fromStdString(obj);
    return QVariant();
}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return "List";
        }
    }
    return QVariant();
}
