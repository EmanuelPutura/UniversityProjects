#ifndef WRITERWINDOW_H
#define WRITERWINDOW_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <controller/controller.h>

namespace Ui {
class WriterWindow;
}

class WriterWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    Ui::WriterWindow *ui;
    QSortFilterProxyModel *model;

    Controller& controller;
    Writer writer;

    QVBoxLayout *layout;
    std::vector<std::pair<QTextEdit*, QPushButton*>> edits;
public:
    explicit WriterWindow(Controller& controller, Writer writer, QSortFilterProxyModel *model, QWidget *parent = nullptr);

    void update() override;
    void updateBtn(bool flag) override;

    int computeAccepted() const;

    ~WriterWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // WRITERWINDOW_H
