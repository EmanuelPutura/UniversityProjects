#include "drawwindow.h"
#include "statisticswindow.h"

#include <QColor>
#include <QLabel>

StatisticsWindow::StatisticsWindow(Controller &controller, QWidget *parent) : QWidget(parent), controller(controller)
{
    setWindowTitle("Statistics");
    layout = new QFormLayout(this);
    setLayout(layout);
}

void StatisticsWindow::update()
{
    delete layout;
    layout = new QFormLayout(this);
    setLayout(layout);

    auto data = controller.programmersData();
    for (const auto& p : data) {
        auto lbl = new QLabel(QString::fromStdString(p.getName()));
        bool blue = (p.getToRevise() == 0);
        if (blue) {
            QColor color = Qt::blue;
            QPalette p = lbl->palette();
            p.setColor(QPalette::WindowText, color);
            lbl->setPalette(p);
        }

        auto w = new DrawWindow(p.getRevisedFiles() * 3, blue);
        layout->addRow(lbl, w);
    }
}

void StatisticsWindow::buttonUpdate(bool flag)
{

}
