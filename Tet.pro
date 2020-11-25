TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Action/action.cpp \
        Figure/figure.cpp \
        GameField/gamefield.cpp \
        GamePlay/gameplay.cpp \
        GlobalConst/globalconst.cpp \
        Utilities/utilities.cpp \
        main.cpp \
    GamePlay/ncurs.cpp

HEADERS += \
    Action/action.h \
    Figure/figure.h \
    GameField/gamefield.h \
    GamePlay/gameplay.h \
    GlobalConst/globalconst.h \
    Utilities/utilities.h \
    GamePlay/drawinterface.h \
    GamePlay/ncurs.h

INCLUDEPATH += /usr/include/ncurses.h
LIBS += -lncurses
