QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase console

TEMPLATE = app

INCLUDEPATH += D:\qtdoc\reamber_base\src
LIBS += -LD:\qtdoc\build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release\release -lreamber_base

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release/release/ -lreamber_base
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release/debug/ -lreamber_base
else:unix: LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release/ -lreamber_base

INCLUDEPATH += $$PWD/../build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release/release
DEPENDPATH += $$PWD/../build-reamber_base-Desktop_Qt_5_12_0_MSVC2017_32bit-Release/release

SOURCES +=  reamber_base_test.cpp
