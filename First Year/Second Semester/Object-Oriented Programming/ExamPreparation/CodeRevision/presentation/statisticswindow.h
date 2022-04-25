#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QFormLayout>
#include <QWidget>

#include <domain/observerpattern.h>

#include <controller/controller.h>

class StatisticsWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    QFormLayout *layout;
    Controller& controller;
public:
    explicit StatisticsWindow(Controller& controller, QWidget *parent = nullptr);
    void update() override;
    void buttonUpdate(bool flag) override;
signals:

};

#endif // STATISTICSWINDOW_H
