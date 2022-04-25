#include "tablemodel.h"

#include <QBrush>
#include <QFont>
#include <QVariant>


TableModel::TableModel(IssueRepository &repository, QObject *parent) : repository(repository), QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return repository.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    auto obj = repository.data()[index.row()];
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return QString::fromStdString(obj.getDescription());
        case 1:
            return QString::fromStdString(obj.getStatus());
        case 2:
            return QString::fromStdString(obj.getReporter());
        case 3:
            return QString::fromStdString(obj.getSolver());
        }
    }
//    else if (role == Qt::FontRole) {
//        if (obj.getStatus() == "not_revised")
//            return QVariant();

//        QFont font;
//        font.setBold(true);
//        return font;
//    }
//    else if (role == Qt::BackgroundRole) {
//        if (obj.getStatus() == "revised")
//            return QVariant();
//        return QBrush(QColor(Qt::green));
//    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Description";
            case 1:
                return "Status";
            case 2:
                return "Creator";
            case 3:
                return "Act";
            }
        }
    }
    return QVariant();
}
