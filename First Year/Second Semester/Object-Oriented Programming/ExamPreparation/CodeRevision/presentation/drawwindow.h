#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>

class DrawWindow : public QWidget
{
    Q_OBJECT
private:
    int radius;
    QPainter *painter;
    bool blue;
public:
    explicit DrawWindow(int radius, bool blue = false, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // DRAWWINDOW_H
