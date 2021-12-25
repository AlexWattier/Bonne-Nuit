TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

win32-g++* {
    QMAKE_CXXFLAGS += -Wa,-mbig-obj
}



include(../config.pri)

SOURCES +=     main.cpp \
    Test_Game.cpp
