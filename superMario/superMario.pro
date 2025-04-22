QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    character.cpp \
    flag.cpp \
    goomba.cpp \
    itemBlock.cpp \
    koopa.cpp \
    levelSelect.cpp \
    main.cpp \
    mainMenu.cpp \
    mainwindow.cpp \
    mushroom.cpp \
    pipe.cpp

HEADERS += \
    block.h \
    character.h \
    flag.h \
    goomba.h \
    itemBlock.h \
    koopa.h \
    levelSelect.h \
    mainMenu.h \
    mainwindow.h \
    mushroom.h \
    pipe.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
