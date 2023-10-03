TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    EdgeFinding/edge.cpp

INCLUDEPATH += D:\opencv_3_1_0\include
LIBS += D:\opencv_3_1_0\x86\mingw\lib\libopencv_world310.dll.a


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    EdgeFinding/edge.h

