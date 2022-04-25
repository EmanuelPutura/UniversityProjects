#include "drawwindow.h"

#include <QBrush>
#include <QPainter>

DrawWindow::DrawWindow(int radius, bool blue, QWidget *parent) : QWidget(parent), radius(radius), blue(blue)
{
    painter = new QPainter(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void DrawWindow::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    painter->eraseRect(this->rect());

    QBrush brush{ Qt::blue, Qt::FDiagPattern };
    if (!blue)
        brush = QBrush { Qt::red, Qt::FDiagPattern };
    painter->setBrush(brush);

    painter->drawEllipse(rect().center(), radius, radius);
    painter->end();
}
