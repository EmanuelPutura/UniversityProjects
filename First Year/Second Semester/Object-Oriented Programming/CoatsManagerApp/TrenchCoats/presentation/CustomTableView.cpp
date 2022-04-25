#include "CustomTableView.h"
#include <QHeaderView>

CustomTableView::CustomTableView(QWidget *parent) : QTableView(parent) {
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->hide();
    horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: rgba(78, 63, 133, 1)}");
    setStyleSheet("background-color: transparent;"
                  "color: rgba(214, 213, 225, 1);"
                  "font: bold Arial;"
                  "font-size: 15px;");
}
