#include "sourcestablemodel.h"

#include <QBrush>
#include <QFont>
#include <QVariant>


SourcesTableModel::SourcesTableModel(SourceFileRepo &sources, QObject *parent) : sources(sources), QAbstractTableModel(parent)
{
}

int SourcesTableModel::rowCount(const QModelIndex &parent) const
{
    return sources.size();
}

int SourcesTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant SourcesTableModel::data(const QModelIndex &index, int role) const
{
    auto obj = sources.data()[index.row()];
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return QString::fromStdString(obj.getName());
        case 1:
            return QString::fromStdString(obj.getStatus());
        case 2:
            return QString::fromStdString(obj.getCreator());
        case 3:
            return QString::fromStdString(obj.getReviewer());
        }
    }
    else if (role == Qt::FontRole) {
        if (obj.getStatus() == "not_revised")
            return QVariant();

        QFont font;
        font.setBold(true);
        return font;
    }
    else if (role == Qt::BackgroundRole) {
        if (obj.getStatus() == "revised")
            return QVariant();
        return QBrush(QColor(Qt::green));
    }
    return QVariant();
}

QVariant SourcesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Name";
            case 1:
                return "Status";
            case 2:
                return "Creator";
            case 3:
                return "Reviewer";
            }
        }
    }
    return QVariant();
}
