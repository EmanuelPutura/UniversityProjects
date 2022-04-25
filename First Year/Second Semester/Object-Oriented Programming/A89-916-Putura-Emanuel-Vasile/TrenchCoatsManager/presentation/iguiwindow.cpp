#include <presentation/IGuiWindow.h>

#include <QLayoutItem>
#include <QPainter>
#include <QRect>

IGuiWindow::IGuiWindow(QWidget *parent) : QWidget(parent) {
}

void IGuiWindow::clearLayout(QLayout *layout) {
    QLayoutItem* child;
    while (layout->count() != 0) {
        child = layout->takeAt ( 0 );
        if (child->layout() != 0)
            clearLayout(child->layout());
        else if (child->widget() != 0)
            delete child->widget();
        delete child;
    }
}

void IGuiWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QRect rectangle = event->rect();
    QPainter painter(this);
    QGradient gradient(QGradient::MidnightBloom);
//    QGradient gradient(QGradient::FarawayRiver);
    painter.fillRect(rectangle, gradient);
}
