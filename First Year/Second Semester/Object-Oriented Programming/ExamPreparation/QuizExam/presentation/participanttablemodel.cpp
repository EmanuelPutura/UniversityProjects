#include "participanttablemodel.h"

#include <QBrush>
#include <QColor>


void ParticipantTableModel::addAnswer(int id)
{
    answered.push_back(id);
}

bool ParticipantTableModel::isAnswered(int id)
{
    for (const auto& ans : answered)
        if (ans == id) return true;
    return false;
}

ParticipantTableModel::ParticipantTableModel(QuestionsRepository &repository, QObject *parent) : repository(repository), QAbstractTableModel(parent)
{
}

int ParticipantTableModel::rowCount(const QModelIndex &parent) const
{
    return repository.size();
}

int ParticipantTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ParticipantTableModel::data(const QModelIndex &index, int role) const
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
    else if (role == Qt::BackgroundRole) {
        bool found = false;
        for (const auto& el : answered) {
            if (el == obj.getID()) {
                found = true;
                break;
            }
        }

        if (!found)
            return QVariant();
        return QBrush(QColor(Qt::green));
    }
    return QVariant();
}

QVariant ParticipantTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "ID";
            case 1:
                return "Text";
            case 2:
                return "Score";
            }
        }
    }
    return QVariant();
}

bool ParticipantTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    endInsertRows();
    return true;
}

bool ParticipantTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    endRemoveRows();
    return true;
}
