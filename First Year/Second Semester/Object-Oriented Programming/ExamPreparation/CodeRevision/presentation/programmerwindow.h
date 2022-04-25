#ifndef PROGRAMMERWINDOW_H
#define PROGRAMMERWINDOW_H

#include "sourcestablemodel.h"

#include <QSortFilterProxyModel>
#include <QWidget>

#include <domain/observerpattern.h>
#include <domain/programmer.h>

#include <controller/controller.h>

namespace Ui {
class ProgrammerWindow;
}

class ProgrammerWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    Ui::ProgrammerWindow *ui;

    Programmer programmer;
    Controller& controller;

    std::string selected;

    QSortFilterProxyModel *model;
public:
    explicit ProgrammerWindow(Programmer programmer, Controller& controller, QSortFilterProxyModel *model, QWidget *parent = nullptr);
    ~ProgrammerWindow();

    void update() override;
    void buttonUpdate(bool flag) override;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);
};

#endif // PROGRAMMERWINDOW_H
