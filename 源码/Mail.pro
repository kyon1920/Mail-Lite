#-------------------------------------------------
#
# Project created by QtCreator 2020-01-07T13:21:48
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mail
TEMPLATE = app
RC_ICONS = ico.ico

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

SOURCES += \
        addfriend.cpp \
        login.cpp \
        main.cpp \
        muitemdelegate.cpp \
        register.cpp \
        widget.cpp

HEADERS += \
        addfriend.h \
        login.h \
        muitemdelegate.h \
        mulistitemdata.h \
        register.h \
        widget.h

FORMS += \
        addfriend.ui \
        login.ui \
        register.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../background/0.gif

RESOURCES +=
