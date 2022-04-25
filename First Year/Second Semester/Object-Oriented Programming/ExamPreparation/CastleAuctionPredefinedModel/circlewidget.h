#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QPainter>
#include <QWidget>

class CircleWidget : public QWidget
{
    Q_OBJECT
private:
    int radius;
    QPainter *painter;
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    explicit CircleWidget(int radius, QWidget *parent = nullptr);
signals:
};

#endif // CIRCLEWIDGET_H
