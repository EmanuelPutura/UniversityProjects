#include "customproxymodel.h"

CustomProxyModel::CustomProxyModel(bool presenter, QObject *parent) : presenter(presenter), QSortFilterProxyModel(parent)
{

}

bool CustomProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (left.column() != right.column())
        return QSortFilterProxyModel::lessThan(left, right);

    int col = 2;
    if (presenter) col = 3;

    if (left.column() != 0 && left.column() != col)
        return QSortFilterProxyModel::lessThan(left, right);

    QVariant leftData = sourceModel()->data(left).toInt();
    QVariant rightData = sourceModel()->data(right).toInt();

    return leftData < rightData;
}
