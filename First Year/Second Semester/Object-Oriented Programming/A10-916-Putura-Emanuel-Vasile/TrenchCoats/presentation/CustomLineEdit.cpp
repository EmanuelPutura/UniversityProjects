#include "CustomLineEdit.h"

CustomLineEdit::CustomLineEdit() : QLineEdit() {
    setStyleSheet("color: rgba(214, 213, 225, 1);"
                  "font: bold Arial;"
                  "font-size: 15px;"
                  "background-color: transparent;"
                  "border: 1px solid rgba(1, 1, 1, 1)");
}
