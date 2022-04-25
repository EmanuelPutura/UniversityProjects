//
// Created by Emanuel on 20.03.2021.
//

#include "testing/TestAll.h"
#include "presentation/AdminConsoleUI/AdminConsoleUI.h"
#include "presentation/OptionConsoleUI/OptionConsoleUI.h"
#include "presentation/UserConsoleUI/UserConsoleUI.h"
#include "presentation/SwitcherConsoleUI/Switcher.h"
#include "infrastructure/FileRepository/FileRepository.h"

#include <fstream>

int main() {
    Testing::TestAll testAll;
    testAll.testAll();

//    Repository<TrenchCoat> repository;
//    Repository<TrenchCoat> shopping_basket;

    FileRepository<TrenchCoat> repository {"../files/repository.txt"};
    FileRepository<TrenchCoat> shopping_basket {"../files/shopping_basket.txt"};
    CoatsService service {repository, shopping_basket};

    AdminConsoleUI adminConsoleUI {service};
    UserConsoleUI userConsoleUI {service};
    OptionConsoleUI optionConsoleUI {service};
    optionConsoleUI.run();
    size_t option = optionConsoleUI.getExitCode();

    switch (option) {
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
