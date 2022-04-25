#include <QApplication>

#include <presentation/presenterwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PresenterWindow w;
    w.show();

    return a.exec();
}
