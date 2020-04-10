QT += testlib gui
CONFIG += qt warn_on depend_includepath testcase console

TEMPLATE = app

SOURCES +=  tst_reamber_base_test.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/Debug/ -lreamber_base
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/debug/ -lreamber_base
else:unix: LIBS += -L$$PWD/../build-reamber_base-Desktop_Qt_5_13_0_MSVC2017_32bit-Debug/ -lreamber_base

INCLUDEPATH += \
$$PWD/../reamber_base \
$$PWD/../reamber_base/include
DEPENDPATH += $$PWD/../reamber_base/include
