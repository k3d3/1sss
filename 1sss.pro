#-------------------------------------------------
#
# Project created by QtCreator 2012-01-08T09:14:45
#
#-------------------------------------------------

QT       += core gui network oauth

CONFIG   += oauth

TARGET = 1sss
TEMPLATE = app


SOURCES += main.cpp\
        region_grabber.cpp \
    config_window.cpp \
    trigger_socket.cpp \
    tray_icon.cpp

HEADERS  += region_grabber.h \
    config_window.h \
    trigger_socket.h \
    tray_icon.h

FORMS +=

INCLUDEPATH += /usr/include/QtCrypto
INCLUDEPATH += /usr/include/QtOAuth

LIBS += -L/usr/lib -lqoauth
LIBS += -L/usr/lib -lqca
