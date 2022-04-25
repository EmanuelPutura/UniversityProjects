QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    domain/issue.cpp \
    domain/observerpattern.cpp \
    domain/user.cpp \
    infrastructure/issuerepository.cpp \
    infrastructure/userrepository.cpp \
    main.cpp \
    presentation/drawwindow.cpp \
    presentation/statisticswindow.cpp \
    presentation/tablemodel.cpp \
    presentation/userwindow.cpp

HEADERS += \
    controller/controller.h \
    domain/issue.h \
    domain/observerpattern.h \
    domain/user.h \
    infrastructure/issuerepository.h \
    infrastructure/userrepository.h \
    presentation/drawwindow.h \
    presentation/statisticswindow.h \
    presentation/tablemodel.h \
    presentation/userwindow.h

FORMS += \
    presentation/userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/issues.txt \
    files/users.txt
