#include "circlewidget.h"


void CircleWidget::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
//    painter->eraseRect(rect());

    QBrush brush{ Qt::red, Qt::FDiagPattern };
    painter->setBrush(brush);

    painter->drawEllipse(rect().center(), radius, radius);
    painter->end();
}

CircleWidget::CircleWidget(int radius, QWidget *parent) : radius(radius), QWidget(parent)
{
//    resize(2 * radius, 2 * radius);
    painter = new QPainter(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
