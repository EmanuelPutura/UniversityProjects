QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cpp \
    domain/idea.cpp \
    domain/observerpattern.cpp \
    domain/writer.cpp \
    exception.cpp \
    infrastructure/idearepo.cpp \
    infrastructure/writerrepo.cpp \
    main.cpp \
    presentation/tablemodel.cpp \
    presentation/writerwindow.cpp

HEADERS += \
    controller/controller.h \
    domain/idea.h \
    domain/observerpattern.h \
    domain/writer.h \
    exception.h \
    infrastructure/idearepo.h \
    infrastructure/writerrepo.h \
    presentation/tablemodel.h \
    presentation/writerwindow.h

FORMS += \
    presentation/writerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/ideas.txt \
    files/writers.txt
