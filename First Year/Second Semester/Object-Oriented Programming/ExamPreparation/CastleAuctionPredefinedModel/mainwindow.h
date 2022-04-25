#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <CastlesModel.h>
#include <CircleWidget.h>
#include <QFormLayout>
#include <QLabel>
#include <QPainter>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <string>

#include <infrastructure/repository.h>
#include <Domain/castle.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Repository repository;

    CastlesModel *custom_model;
    QSortFilterProxyModel *proxy_model;

    std::vector<std::pair<CircleWidget*, QLabel*>> circles;
//    QFormLayout *flayout;
    QGridLayout *layout;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    void init();
};

#endif // MAINWINDOW_H
