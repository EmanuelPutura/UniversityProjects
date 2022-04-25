#include "castlesmodel.h"

#include <QFont>


CastlesModel::CastlesModel(Repository &repository, QObject *parent) : repository(repository), QAbstractTableModel(parent)
{
}

int CastlesModel::rowCount(const QModelIndex &parent) const
{
    return repository.size();
}

int CastlesModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant CastlesModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();
    auto element = repository.data()[row];

    if (role == Qt::DisplayRole)
    {
        switch(column)
        {
        case 0:
            return QString::fromStdString(element.getName());
        case 1:
            return QString::fromStdString(element.getLocation());
        case 2:
            return QString::number(element.getStartingPrice());
        case 3:
            return QString::number(element.getCurrentPrice());
        default:
            break;
        }
    }
    else if (role == Qt::FontRole)
    {
        QFont font("Arial");
        return font;
    }
    return QVariant();
}

QVariant CastlesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("Location");
                case 2:
                    return QString("Starting Price");
                case 3:
                    return QString("Current Price");
            default:
                break;
            }
        }
    }
    else if (role == Qt::FontRole)
    {
        QFont font("Arial");
        return font;
    }
    return QVariant();
}
