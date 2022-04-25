#include "drawwindow.h"
#include "statisticswindow.h"

#include <QLabel>
#include <QDebug>
#include <set>

StatisticsWindow::StatisticsWindow(Controller &controller, QWidget *parent) : QWidget(parent), controller(controller)
{
    layout = new QFormLayout;
    setLayout(layout);
    resize(300, 300);
}

void StatisticsWindow::update()
{
    delete layout;
    layout = new QFormLayout;
    setLayout(layout);

    std::set<std::string> names;
    for (const auto& u : controller.userData())
        names.insert(u.getName());

    for (const auto& u : names) {
        int cnt = 0;
        for (const auto& i : controller.issueData())
            if (i.getSolver() == u) cnt++;

        auto lbl = new QLabel(QString::fromStdString(u));
        auto w = new DrawWindow {cnt};
        layout->addRow(lbl, w);
    }
}

void StatisticsWindow::updateBtn(bool flag)
{

}
