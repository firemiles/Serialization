QT += core
QT -= gui

CONFIG += c++11

TARGET = base
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    ../../include/serialization.h
