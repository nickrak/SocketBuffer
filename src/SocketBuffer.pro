#-------------------------------------------------
#
# Project created by QtCreator 2011-06-18T20:30:45
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = SocketBuffer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    socketbuffermanager.cpp \
    serverpair.cpp

HEADERS += \
    socketbuffermanager.h \
    serverpair.h
