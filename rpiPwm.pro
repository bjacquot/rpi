QT += core
QT -= gui

CONFIG += c++11

TARGET = rpiPwm
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    io/pwmclk.cpp \
    io/rpiperipherique.cpp \
    io/pwm.cpp \
    io/gpio.cpp
HEADERS += \
    io/pwmclk.h \
    io/rpiperipherique.h \
    io/pwm.h \
    io/gpio.h
