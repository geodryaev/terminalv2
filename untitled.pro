#-------------------------------------------------
#
# Project created by QtCreator 2024-09-23T12:24:15
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
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

CONFIG += c++11
CONFIG += private

RESOURCES += resources.qrc

INCLUDEPATH += C:\Qt\Qt5.11.3\5.11.3\mingw53_32\include\QtGui\5.11.3
INCLUDEPATH += C:\Qt\Qt5.11.3\5.11.3\mingw53_32\include\QtCore\5.11.3

SOURCES += \
    aboutme.cpp \
        main.cpp \
        mainwindow.cpp \
    widgetdelegate.cpp \
    passwd.cpp \
    dialogfromupdatefiles.cpp \
    dialogsetpathtosave.cpp \
    listgansta.cpp

HEADERS += \
    aboutme.h \
        mainwindow.h \
    widgetdelegate.h \
    passwd.h \
    dialogfromupdatefiles.h \
    dialogsetpathtosave.h \
    listgansta.h

FORMS += \
    aboutme.ui \
        mainwindow.ui \
    passwd.ui \
    dialogfromupdatefiles.ui \
    dialogsetpathtosave.ui \
    listgansta.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
