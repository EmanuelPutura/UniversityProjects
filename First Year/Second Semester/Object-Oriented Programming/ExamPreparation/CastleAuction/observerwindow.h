#ifndef OBSERVERWINDOW_H
#define OBSERVERWINDOW_H

#include <QWidget>
#include <QCheckBox>

#include <Domain/observerpattern.h>
#include <Controller/subjectcontroller.h>
#include <Presentation/castlestablemodel.h>

namespace Ui {
class ObserverWindow;
}

class ObserverWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    void initCheckBoxes();
public:
    explicit ObserverWindow(SubjectController& service, QWidget *parent = nullptr);

    void update() override;
    void updateCheckBox(std::string castle, bool value) override;

    ~ObserverWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ObserverWindow *ui;
    CastlesTableModel *model;

    SubjectController& service;
    std::vector<QCheckBox*> checkboxes;
signals:
    void newBidSignal();
};

#endif // OBSERVERWINDOW_H
