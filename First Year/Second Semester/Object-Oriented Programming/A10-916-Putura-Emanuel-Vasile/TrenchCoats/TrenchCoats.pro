QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    business/CoatsService.cpp \
    business/IService.cpp \
    business/UndoRedoService.cpp \
    domain/FunctionsData/AddFunctionCall.cpp \
    domain/FunctionsData/BasketAddFunctionCall.cpp \
    domain/FunctionsData/BasketRemoveFunctionCall.cpp \
    domain/FunctionsData/IFunctionCall.cpp \
    domain/FunctionsData/RemoveFunctionCall.cpp \
    domain/FunctionsData/UndoRedoFunction.cpp \
    domain/FunctionsData/UpdateFunctionCall.cpp \
    domain/TrenchCoat/TrenchCoat.cpp \
    exceptions/ConsoleUIException/ConsoleUIException.cpp \
    exceptions/Exception/Exception.cpp \
    exceptions/RepositoryException/RepositoryException.cpp \
    exceptions/ServiceException/ServiceException.cpp \
    infrastructure/AbstractLaunchRepository/AbstractLaunchRepository.cpp \
    infrastructure/AbstractRepository/AbstractRepository.cpp \
    infrastructure/CSVRepository/CSVRepository.cpp \
    infrastructure/FileRepository/FileRepository.cpp \
    infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.cpp \
    main.cpp \
    presentation/CoatPictureDelegate.cpp \
    presentation/CoatsTableModel.cpp \
    presentation/CustomButton.cpp \
    presentation/CustomLabel.cpp \
    presentation/CustomLineEdit.cpp \
    presentation/CustomTableView.cpp \
    presentation/GUIAdminWindow.cpp \
    presentation/GUIOptionWindow.cpp \
    presentation/GUIUserWindow.cpp \
    presentation/iguiwindow.cpp \
    tools/Launcher.cpp \
    validation/CoatValidator.cpp

HEADERS += \
    business/CoatsService.h \
    business/IService.h \
    business/UndoRedoService.h \
    domain/FunctionsData/AddFunctionCall.h \
    domain/FunctionsData/BasketAddFunctionCall.h \
    domain/FunctionsData/BasketRemoveFunctionCall.h \
    domain/FunctionsData/IFunctionCall.h \
    domain/FunctionsData/RemoveFunctionCall.h \
    domain/FunctionsData/UndoRedoFunction.h \
    domain/FunctionsData/UpdateFunctionCall.h \
    domain/TrenchCoat/TrenchCoat.h \
    exceptions/ConsoleUIException/ConsoleUIException.h \
    exceptions/Exception/Exception.h \
    exceptions/RepositoryException/RepositoryException.h \
    exceptions/ServiceException/ServiceException.h \
    infrastructure/AbstractLaunchRepository/AbstractLaunchRepository.h \
    infrastructure/AbstractRepository/AbstractRepository.h \
    infrastructure/CSVRepository/CSVRepository.h \
    infrastructure/FileRepository/FileRepository.h \
    infrastructure/HTMLCoatsRepository/HTMLCoatsRepository.h \
    infrastructure/Repository/Repository.h \
    infrastructure/Repository/Repository.inl \
    presentation/CoatPictureDelegate.h \
    presentation/CoatsTableModel.h \
    presentation/CustomButton.h \
    presentation/CustomLabel.h \
    presentation/CustomLineEdit.h \
    presentation/CustomTableView.h \
    presentation/GUIAdminWindow.h \
    presentation/GuiOptionWindow.h \
    presentation/GuiUserWindow.h \
    presentation/IGuiWindow.h \
    tools/Launcher.h \
    validation/CoatValidator.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/red.jpg \
    files/repository.txt \
    files/shopping_basket.csv \
    files/shopping_basket.html \
    images/red.jpg
