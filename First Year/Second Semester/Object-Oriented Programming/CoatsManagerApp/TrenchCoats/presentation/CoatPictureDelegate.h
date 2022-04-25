#ifndef COATPICTUREDELEGATE_H
#define COATPICTUREDELEGATE_H

#include <QStyledItemDelegate>

class CoatPictureDelegate : public QStyledItemDelegate {
public:
    explicit CoatPictureDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // COATPICTUREDELEGATE_H
