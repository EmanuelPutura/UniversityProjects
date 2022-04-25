#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QModelIndex>
#include <QVariant>
#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
private:
    bool presenter;
public:
    explicit CustomProxyModel(bool presenter, QObject *parent = nullptr);

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

#endif // CUSTOMPROXYMODEL_H
