#ifndef IGUIWINDOW_H
#define IGUIWINDOW_H

#include <QLayout>
#include <QPaintEvent>
#include <QWidget>

class IGuiWindow : public QWidget {
    Q_OBJECT
protected:
    void clearLayout(QLayout* layout);
    virtual void display() = 0;
    void paintEvent(QPaintEvent* event) override;
public:
    explicit IGuiWindow(QWidget *parent = nullptr);
signals:
    void adminSwitch();
    void userSwitch();
};

#endif // IGUIWINDOW_H
