cmake_minimum_required(VERSION 3.16)
project(a67_916_Putura_Emanuel_Vasile)

set(CMAKE_CXX_STANDARD 14)

find_package(SQLite3)

add_executable(a67_916_Putura_Emanuel_Vasile
        main.cpp
        domain/TrenchCoat/TrenchCoat.h
        domain/TrenchCoat/TrenchCoat.cpp
        testing/TestAll.h
        testing/TestAll.cpp
        infrastructure/Repository/Repository.h
        infrastructure/Repository/Repository.inl
        business/CoatsService.h
        business/CoatsService.cpp
        validation/CoatValidator.h
        validation/CoatValidator.cpp presentation/GenericConsoleUI/ConsoleUI.h presentation/GenericConsoleUI/ConsoleUI.cpp presentation/AdminConsoleUI/AdminConsoleUI.h presentation/AdminConsoleUI/AdminConsoleUI.cpp presentation/TextTable/TextTable.h presentation/TextTable/TextTable.cpp presentation/UserConsoleUI/UserConsoleUI.h presentation/UserConsoleUI/UserConsoleUI.cpp presentation/OptionConsoleUI/OptionConsoleUI.h presentation/OptionConsoleUI/OptionConsoleUI.cpp presentation/SwitcherConsoleUI/Switcher.h presentation/SwitcherConsoleUI/Switcher.cpp tools/Launcher.h tools/Launcher.cpp infrastructure/AbstractRepository/AbstractRepository.cpp infrastructure/AbstractRepository/AbstractRepository.h exceptions/Exception/Exception.cpp exceptions/Exception/Exception.h exceptions/RepositoryException/RepositoryException.cpp exceptions/RepositoryException/RepositoryException.h exceptions/ServiceException/ServiceException.cpp exceptions/ServiceException/ServiceException.h exceptions/ConsoleUIException/ConsoleUIException.cpp exceptions/ConsoleUIException/ConsoleUIException.h infrastructure/FileRepository/FileRepository.cpp infrastructure/FileRepository/FileRepository.h infrastructure/CSVRepository/CSVRepository.cpp infrastructure/CSVRepository/CSVRepository.h infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.cpp infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.h infrastructure/AbstractLaunchRepository/AbstractLaunchRepository.cpp infrastructure/AbstractLaunchRepository/AbstractLaunchRepository.h infrastructure/DatabaseCoatsRepository/DatabaseCoatsRepository.cpp infrastructure/DatabaseCoatsRepository/DatabaseCoatsRepository.h)

target_include_directories(a67_916_Putura_Emanuel_Vasile PRIVATE include/)
target_link_libraries(a67_916_Putura_Emanuel_Vasile PRIVATE SQLite::SQLite)
target_link_libraries(a67_916_Putura_Emanuel_Vasile LINK_PUBLIC sqlite3)

if(WIN32)
    set(SQLite3_INCLUDE_DIR C:\\sqlite\\include)
    set(SQLite3_LIBRARY_DIR C:\\sqlite\\lib)
    set(SQLite3_LIBRARY sqlite3.dll)
endif()

find_package(SQLite3 REQUIRED)
target_include_directories(a67_916_Putura_Emanuel_Vasile PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_directories(a67_916_Putura_Emanuel_Vasile PRIVATE ${SQLite3_LIBRARY_DIR})
