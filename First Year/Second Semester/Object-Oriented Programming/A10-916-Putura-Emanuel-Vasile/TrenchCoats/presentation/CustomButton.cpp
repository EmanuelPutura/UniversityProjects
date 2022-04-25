#include "CustomButton.h"

#include <QPainter>
#include <QPalette>
#include <QGradient>
#include <QRect>

CustomButton::CustomButton(const QString& text, QWidget* parent) : QPushButton(text, parent) {
    setFixedHeight(40);
    setStyleSheet("color: rgba(214, 213, 225, 1);"
                  "font: bold Arial;"
                  "font-size: 15px;"
                  "border: 1px solid rgba(1, 1, 1, 1);"
                  "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0.273, stop:0 rgba(65, 60, 120, 0), stop:1 rgba(38, 33, 108, 1))");
    //    setStyleSheet("color: rgba(214, 213, 225, 1);"
//                  "font: bold Arial;"
//                  "font-size: 15px;"
//                  "border: 1px solid rgba(1, 1, 1, 1);"
//                  "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0.273, stop:0 rgba(40, 40, 45, 1), stop:1 rgba(25, 25, 30, 1))");
}

