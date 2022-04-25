#include "CoatsTableModel.h"

#include <QBrush>
#include <QFont>
#include <QGradient>
#include <QString>
#include <QDebug>

CoatsTableModel::CoatsTableModel(CoatsService &service, bool basket_entities, QObject *parent) : QAbstractTableModel(parent), service(service), basket_entities(basket_entities) {
}

int CoatsTableModel::rowCount(const QModelIndex &parent) const {
    int rows = service.getLength();
    if (basket_entities) rows = service.getShoppingBasket().size();
    return rows;
}

int CoatsTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant CoatsTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    auto data = service.getData();
    if (basket_entities) data = service.getShoppingBasket();

    auto element = data[row];

    switch (role) {
        case Qt::DisplayRole: {
            switch (column) {
                case 0:
                    return "";
                case 1:
                    return QString::fromStdString(element.getSize());
                case 2:
                    return QString::fromStdString(element.getColour());
                case 3:
                    return QString::number(element.getPrice());
                case 4:
                    return QString::number(element.getQuantity());
                case 5:
                    return QString::fromStdString(element.getPhotograph());
            }
            break;
        }
        case Qt::FontRole: {
            QFont font("Arial");
            font.setBold(true);
            return font;
        }
        case Qt::BackgroundRole: {
            return QBrush(QGradient(QGradient::MidnightBloom));
        }
    }

    return QVariant();
}

QVariant CoatsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch (role) {
        case Qt::DisplayRole: {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0:
                        return QString("Image");
                    case 1:
                        return QString("Size");
                    case 2:
                        return QString("Colour");
                    case 3:
                        return QString("Price");
                    case 4:
                        return QString("Quantity");
                    case 5:
                        return QString("Link");
                }
            }
            break;
        }
        case Qt::FontRole: {
            QFont font("Arial");
            font.setBold(true);
            return font;
        }
        case Qt::BackgroundRole: {
            return QBrush(QGradient(QGradient::MidnightBloom));
        }
    }

    return QVariant();
}
