QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    domain/observerpattern.cpp \
    domain/programmer.cpp \
    domain/sourcefile.cpp \
    infrastructure/programmerrepo.cpp \
    infrastructure/sourcefilerepo.cpp \
    main.cpp \
    presentation/drawwindow.cpp \
    presentation/programmerwindow.cpp \
    presentation/sourcestablemodel.cpp \
    presentation/statisticswindow.cpp

HEADERS += \
    controller/controller.h \
    domain/observerpattern.h \
    domain/programmer.h \
    domain/sourcefile.h \
    infrastructure/programmerrepo.h \
    infrastructure/sourcefilerepo.h \
    presentation/drawwindow.h \
    presentation/programmerwindow.h \
    presentation/sourcestablemodel.h \
    presentation/statisticswindow.h

FORMS += \
    presentation/programmerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/programmers.txt \
    files/sources.txt
