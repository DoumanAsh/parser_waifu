#-------------------------------------------------
#
# Project created by QtCreator 2017-07-14T21:57:34
#
#-------------------------------------------------

QT       += core gui widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParserWaifu
TEMPLATE = app

include(version.pri)

DEFINES += TW_VERSION=\\\"$${PROJECT_VERSION}\\\"
DEFINES += TW_VERSION_MAJOR=$${VER_MAJOR}
DEFINES += TW_VERSION_MINOR=$${VER_MINOR}
DEFINES += TW_VERSION_PATCH=$${VER_PATCH}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:RC_ICONS += assets/img/tw_icon.ico

SOURCES += \
        src/main.cpp \
        src/ui/mainwindow.cpp \
    src/ui/about.cpp

HEADERS += \
        src/ui/mainwindow.hpp \
    src/ui/about.hpp

FORMS += \
        src/ui/mainwindow.ui \
    src/ui/about.ui

# third party stuff
include(3pp/3pp.pri)
