//
// Created by Emanuel on 20.03.2021.
//

#include "testing/TestAll.h"
#include "presentation/AdminConsoleUI/AdminConsoleUI.h"
#include "presentation/OptionConsoleUI/OptionConsoleUI.h"
#include "presentation/UserConsoleUI/UserConsoleUI.h"
#include "presentation/SwitcherConsoleUI/Switcher.h"
#include "infrastructure/FileRepository/FileRepository.h"
#include "infrastructure/CSVRepository/CSVRepository.h"
#include "infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.h"
#include "infrastructure/DatabaseCoatsRepository/DatabaseCoatsRepository.h"


int main() {
    Testing::TestAll testAll;
    testAll.testAll();

//    Repository<TrenchCoat> repository;
//    Repository<TrenchCoat> shopping_basket;

    OptionConsoleUI optionConsoleUI;
    optionConsoleUI.run();
    size_t mode_option = optionConsoleUI.getExitCode();
    size_t basket_option = optionConsoleUI.getBasketType();

    FileRepository<TrenchCoat> repository {"../files/repository.txt"};
//    DatabaseCoatsRepository repository {"..\\databases\\repository.db"};

    AbstractLaunchRepository<TrenchCoat>* shopping_basket;
    CSVRepository<TrenchCoat> shopping_basket_csv("..\\files\\shopping_basket.csv");
    HTMLCoatsRepository shopping_basket_html("..\\files\\shopping_basket.html");

    if (basket_option) shopping_basket = &shopping_basket_html;
    else shopping_basket = &shopping_basket_csv;

    CoatsService service {repository, *shopping_basket};

    AdminConsoleUI adminConsoleUI {service};
    UserConsoleUI userConsoleUI {service};

    switch (mode_option) {
        case 1:
        {
            Switcher switcher {adminConsoleUI, userConsoleUI};
            switcher.run();
            break;
        }
        case 2:
        {
            Switcher switcher {userConsoleUI, adminConsoleUI};
            switcher.run();
            break;
        }
        default:
            break;
    }

    return 0;
}
