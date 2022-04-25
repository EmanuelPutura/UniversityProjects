#include "drawwindow.h"

#include <QPen>

DrawWindow::DrawWindow(int solved, QWidget *parent) : QWidget(parent), solved(solved)
{
    painter = new QPainter(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void DrawWindow::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    painter->eraseRect(this->rect());

    QBrush brush{ Qt::green, Qt::FDiagPattern };
    QPen pen;
    pen.setWidth(5);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawLine(30, 30, 30 + solved * 10, 30);
    painter->end();
}
