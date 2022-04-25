#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <controller/controller.h>

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    Ui::UserWindow *ui;

    Controller& controller;
    QSortFilterProxyModel *model;
    User user;
public:
    explicit UserWindow(Controller& controller, User user, QSortFilterProxyModel *model, QWidget *parent = nullptr);

    void update() override;
    void updateBtn(bool flag) override;

    ~UserWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_3_clicked();
};

#endif // USERWINDOW_H
