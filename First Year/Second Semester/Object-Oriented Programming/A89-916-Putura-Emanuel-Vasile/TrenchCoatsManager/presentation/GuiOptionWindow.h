#ifndef GUIOPTIONWINDOW_H
#define GUIOPTIONWINDOW_H

#include <QPushButton>
#include <QWidget>
#include <QCloseEvent>


class GuiOptionWindow : public QWidget {
    Q_OBJECT
private:
    int flag = 0;
    bool basket_type = false;

    QPushButton* admin_button;
    QPushButton* user_button;
    QPushButton* change_button;
    QPushButton* exit_button;
public:
    explicit GuiOptionWindow(QWidget *parent = 0);
    ~GuiOptionWindow();

    void closeEvent(QCloseEvent *event) override;

    inline int getFlag() const { return flag; }
    inline bool getBasketType() const { return basket_type; }
private:
    void initWindow();
    void connect();

    void paintEvent(QPaintEvent* event) override;
signals:
    void flagChange();
};

#endif // GUIOPTIONWINDOW_H
