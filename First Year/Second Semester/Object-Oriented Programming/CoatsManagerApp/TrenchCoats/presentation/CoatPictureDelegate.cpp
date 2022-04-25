#include "CoatPictureDelegate.h"

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>

CoatPictureDelegate::CoatPictureDelegate(QObject *parent) : QStyledItemDelegate(parent) {
}

void CoatPictureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() != 0) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    auto colour_index = index.model()->index(index.row(), 2);
    QString color = index.model()->data(colour_index).toString();
    QPixmap pixmap("../TrenchCoats/images/" + color + ".jpg");
    if (pixmap.isNull()) pixmap = QPixmap("../TrenchCoats/images/default.jpg");
    painter->drawPixmap(option.rect, pixmap);
}

QSize CoatPictureDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 0) {
        return QSize(50, 60);
    }

    return QStyledItemDelegate::sizeHint(option, index);
}
