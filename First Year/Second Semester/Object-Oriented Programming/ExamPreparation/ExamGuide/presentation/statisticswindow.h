#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QFormLayout>
#include <QWidget>

#include <controller/controller.h>

class StatisticsWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    Controller& controller;

    QFormLayout *layout;
public:
    explicit StatisticsWindow(Controller& controller, QWidget *parent = nullptr);

    void update() override;
    void updateBtn(bool flag) override;
signals:

};

#endif // STATISTICSWINDOW_H
