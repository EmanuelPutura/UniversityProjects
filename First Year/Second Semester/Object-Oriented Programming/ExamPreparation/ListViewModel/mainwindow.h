#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ListModel.h>
#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ListModel *model;
    QSortFilterProxyModel *proxy;

    std::vector<std::string> data;
};
#endif // MAINWINDOW_H
