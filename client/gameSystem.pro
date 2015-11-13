#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T10:38:53
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
        configureserverdialog.cpp \
        guessnum.cpp \
        blackjack.cpp \
        ../lib/connection.cpp \
        ../model/build/main.model.pb.cc \
        ../model/build/guess.model.pb.cc \
        ../model/build/jack.model.pb.cc \
        ../model/build/system.model.pb.cc \
        changename.cpp \
    request.cpp \
    blackjackresultdialog.cpp


HEADERS  += mainwindow.h \
    configureserverdialog.h \
    guessnum.h \
    blackjack.h \
    ../lib/connection.hpp \
    ../model/build/main.model.pb.h \
    ../model/build/guess.model.pb.h \
    ../model/build/jack.model.pb.h \
    ../model/build/system.model.pb.h \
    changename.h \
    request.h \
    config.h \
    blackjackresultdialog.h

FORMS    += mainwindow.ui \
            configureserverdialog.ui \
            guessnum.ui \
            blackjack.ui \
            changename.ui \
    blackjackresultdialog.ui

 DESTDIR=../build
 OBJECTS_DIR=../build/bin/client
 MOC_DIR=../build/bin/client


unix:!macx: LIBS += -L../lib/protobuf-2.6.1/src/.libs/ -lprotoc  -lprotobuf

INCLUDEPATH += ../lib/protobuf-2.6.1/src/.libs   ../lib ../model/build/
DEPENDPATH += ../lib/protobuf-2.6.1/src/.libs

unix:!macx: PRE_TARGETDEPS += ../lib/protobuf-2.6.1/src/.libs/libprotoc.a
