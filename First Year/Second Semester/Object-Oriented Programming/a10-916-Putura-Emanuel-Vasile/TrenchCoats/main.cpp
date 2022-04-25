#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QEventLoop>
#include <QLabel>
#include <QPixmap>
#include <memory>

#include <business/CoatsService.h>
#include <business/UndoRedoService.h>
#include <domain/TrenchCoat/TrenchCoat.h>
#include <infrastructure/CSVRepository/CSVRepository.h>
#include <infrastructure/FileRepository/FileRepository.h>
#include <infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.h>
#include <presentation/GuiOptionWindow.h>
#include <presentation/GuiAdminWindow.h>
#include <presentation/GuiUserWindow.h>
#include <domain/FunctionsData/UndoRedoFunction.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileRepository<TrenchCoat> repository {"../TrenchCoats/files/repository.txt"};
    AbstractLaunchRepository<TrenchCoat>* shopping_basket;
    Repository<UndoRedoFunction*> undo_redo_repository;

    CSVRepository<TrenchCoat> shopping_basket_csv("../TrenchCoats/files/shopping_basket.csv");
    HTMLCoatsRepository shopping_basket_html("../TrenchCoats/files/shopping_basket.html");

    GuiOptionWindow option_window;
    option_window.show();

    QEventLoop loop;
    QObject::connect(&option_window, &GuiOptionWindow::flagChange, &loop, &QEventLoop::quit);
    loop.exec();

    int option = option_window.getFlag();
    if (option == -1) {  // exit case
        option_window.close();
        exit(0);
    }

    int basket_option = option_window.getBasketType();
    if (basket_option) shopping_basket = &shopping_basket_csv;
    else shopping_basket = &shopping_basket_html;

    UndoRedoService undo_redo_service {undo_redo_repository};
    CoatsService service {repository, *shopping_basket, undo_redo_service};

    std::unique_ptr<IGuiWindow> admin_window = std::make_unique<GuiAdminWindow>(service);
    std::unique_ptr<IGuiWindow> user_window = std::make_unique<GuiUserWindow>(service);

    // admin case
    if (option == 1)
        admin_window->show();
    else if (option == 2)  // user case
        user_window->show();
    option_window.close();

    QObject::connect(admin_window.get(), &IGuiWindow::adminSwitch, [&](){
        user_window->show();
        admin_window->close();
    });
    QObject::connect(user_window.get(), &IGuiWindow::userSwitch, [&](){
        admin_window->show();
        user_window->close();
    });

    return a.exec();
}
