#-------------------------------------------------
#
# Project created by QtCreator 2015-11-05T09:03:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RPiTC
TEMPLATE = app


SOURCES += main.cpp\
        rpitc.cpp \
    helperwindow.cpp

HEADERS  += rpitc.h \
    helperwindow.h

FORMS    += rpitc.ui \
    helperwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
