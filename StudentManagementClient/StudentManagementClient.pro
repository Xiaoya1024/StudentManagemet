#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T16:47:49
#
#-------------------------------------------------

QT       += core gui
QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentManagementClient
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
    mysocket.cpp \
    studentwindow.cpp \
    managerwindow.cpp \
    assistantwindow.cpp \
    teacherwindow.cpp \
    masterwindow.cpp

HEADERS += \
    mysocket.h \
    protocol.h \
    studentwindow.h \
    managerwindow.h \
    assistantwindow.h \
    teacherwindow.h \
    masterwindow.h

FORMS += \
    mysocket.ui \
    studentwindow.ui \
    managerwindow.ui \
    assistantwindow.ui \
    teacherwindow.ui \
    masterwindow.ui

RESOURCES += \
    img.qrc
