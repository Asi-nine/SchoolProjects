TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    user.cpp \
    account.cpp \
    datamanagement.cpp \
    bank.cpp \
    tracer.cpp \
    mainwindow.cpp

HEADERS += \
    user.h \
    account.h \
    datamanagement.h \
    bank.h \
    tracer.h \
    mainwindow.h
