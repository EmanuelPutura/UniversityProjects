#include "presentertablemodel.h"

PresenterTableModel::PresenterTableModel(QuestionsRepository &repository, QObject *parent) : repository(repository), QAbstractTableModel(parent)
{
}

int PresenterTableModel::rowCount(const QModelIndex &parent) const
{
    return repository.size();
}

int PresenterTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant PresenterTableModel::data(const QModelIndex &index, int role) const
{
    auto obj = repository.data()[index.row()];
    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return QString::number(obj.getID());
        case 1:
            return QString::fromStdString(obj.getText());
        case 2:
            return QString::fromStdString(obj.getCorrect());
        case 3:
            return QString::number(obj.getScore());
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

QVariant PresenterTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "ID";
            case 1:
                return "Text";
            case 2:
                return "Correct answer";
            case 3:
                return "Score";
            }
        }
    }
    return QVariant();
}

bool PresenterTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    endInsertRows();
    return true;
}

bool PresenterTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    endRemoveRows();
    return true;
}
