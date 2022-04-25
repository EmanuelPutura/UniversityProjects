QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    domain/observerpattern.cpp \
    domain/participant.cpp \
    domain/question.cpp \
    exceptions/exception.cpp \
    infrastructure/participant_repo.cpp \
    infrastructure/questions_repo.cpp \
    main.cpp \
    presentation/customproxymodel.cpp \
    presentation/participanttablemodel.cpp \
    presentation/participantwindow.cpp \
    presentation/presentertablemodel.cpp \
    presentation/presenterwindow.cpp

HEADERS += \
    domain/observerpattern.h \
    domain/participant.h \
    domain/question.h \
    exceptions/exception.h \
    infrastructure/participant_repo.h \
    infrastructure/questions_repo.h \
    presentation/customproxymodel.h \
    presentation/participanttablemodel.h \
    presentation/participantwindow.h \
    presentation/presentertablemodel.h \
    presentation/presenterwindow.h

FORMS += \
    presentation/participantwindow.ui \
    presentation/presenterwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    files/participants.txt \
    files/questions.txt
