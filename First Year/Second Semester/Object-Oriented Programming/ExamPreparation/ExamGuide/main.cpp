 #include <QApplication>

#include <controller/controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller controller;

    return a.exec();
}
