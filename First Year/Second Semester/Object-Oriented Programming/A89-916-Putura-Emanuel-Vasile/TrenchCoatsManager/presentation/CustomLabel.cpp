#include "CustomLabel.h"

CustomLabel::CustomLabel(const QString& text) : QLabel(text) {
    setStyleSheet("color: rgba(214, 213, 225, 1);"
                  "font: bold Arial;"
                  "font-size: 15px;");
}
