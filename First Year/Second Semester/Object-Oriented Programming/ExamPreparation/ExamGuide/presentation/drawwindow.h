#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QPainter>
#include <QWidget>
#include <string>

class DrawWindow : public QWidget
{
    Q_OBJECT
private:
    int solved;
    QPainter *painter;
public:
    explicit DrawWindow(int solved, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // DRAWWINDOW_H
