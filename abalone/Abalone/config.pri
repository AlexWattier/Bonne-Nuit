CONFIG += c++17
CONFIG -= debug_and_release debug_and_release_target

INCLUDEPATH += $${PWD}/libs/

include($${PWD}/src/abalone/abalonec.pri)

QMAKE_CXXFLAGS += -Wall
