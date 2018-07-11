#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T22:14:18
#
#-------------------------------------------------

QT       += core gui sql
QT += serialport xml
QT += 3dextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Can3DWiget
TEMPLATE = app
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    readserialdata.cpp \
    mainwindow.cpp \
    config.cpp \
    modelinteract.cpp \
    box.cpp

HEADERS += \
    readserialdata.h \
    config.h \
    mainwindow.h \
    modelinteract.h \
    box.h

FORMS += \
        mainwindow.ui


RESOURCES += \
    source.qrc


#unix:!macx: LIBS += -L$$PWD/../../../../Qt510static/lib/ -lQt5Core

#INCLUDEPATH += $$PWD/../../../../Qt510static/include
#DEPENDPATH += $$PWD/../../../../Qt510static/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../Qt510static/lib/libQt5Core.a

#unix:!macx: LIBS += -L$$PWD/../../../../Qt510static/lib/ -lQt5Multimedia

#INCLUDEPATH += $$PWD/../../../../Qt510static/include
#DEPENDPATH += $$PWD/../../../../Qt510static/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../Qt510static/lib/libQt5Multimedia.a

#unix:!macx: LIBS += -L$$PWD/../../../../Qt510static/lib/ -lQt5SerialPort

#INCLUDEPATH += $$PWD/../../../../Qt510static/include
#DEPENDPATH += $$PWD/../../../../Qt510static/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../Qt510static/lib/libQt5SerialPort.a

#unix:!macx: LIBS += -L$$PWD/../../../../Qt510static/lib/ -lQt5Gui

#INCLUDEPATH += $$PWD/../../../../Qt510static/include
#DEPENDPATH += $$PWD/../../../../Qt510static/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../Qt510static/lib/libQt5Gui.a

DISTFILES += \
    can3D.db
