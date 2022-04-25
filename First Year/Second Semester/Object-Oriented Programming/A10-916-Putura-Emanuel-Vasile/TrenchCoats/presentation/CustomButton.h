#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPaintEvent>
#include <QPushButton>

class CustomButton : public QPushButton {
public:
    CustomButton(const QString& text, QWidget* parent = 0);
};

#endif // CUSTOMBUTTON_H
