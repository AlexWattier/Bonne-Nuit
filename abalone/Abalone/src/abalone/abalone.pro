QT -= qt

TEMPLATE = lib
CONFIG += staticlib

include(../../config.pri)

SOURCES += \
    Board.cpp \
    Case.cpp \
    Position.cpp \
    Game.cpp \
    BoardRules.cpp \
    Model.cpp \
    Controller.cpp


HEADERS += \
    Board.h \
    Case.h \
    Position.h \
    Model.h \
    Game.h \
    BoardRules.h \
    Controller.h \
    InterfaceView.h


DISTFILES += \
    abalonec.pri
