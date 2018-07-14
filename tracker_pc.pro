#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T10:49:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

TARGET = tracker_demo

TEMPLATE = app
DESTDIR = $$PWD

#INCLUDEPATH += /usr/include/opencv \
#            ./resources
INCLUDEPATH += ./resources

SOURCES +=  tracker/fhog.cpp \
    tracker/kcftracker.cpp \
    main/main.cpp \
    main/mainwindow.cpp \
    main/engine.cpp \
    main/run_tracker.cpp \
    tracker/kalman_filter.cpp \
    frame_input/frameinput.cpp \
    main/capturescreen.cpp

HEADERS  += tracker/ffttools.hpp \
    tracker/fhog.hpp \
    tracker/kcftracker.hpp \
    tracker/labdata.hpp \
    tracker/recttools.hpp \
    tracker/tracker.h \
    main/defs.h \
    main/mainwindow.h \
    main/engine.h \
    main/run_tracker.h \
    tracker/kalman_filter.h \
    frame_input/frameinput.hpp \
    main/capturescreen.h

FORMS    +=   main/mainwindow.ui
