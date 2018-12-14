#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T10:36:02
#
#-------------------------------------------------

QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyecto_FInal
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    item_grafico.cpp \
    movimiento.cpp \
    objeto_mov.cpp \
    intro.cpp \
    nombre_partida.cpp \
    data_base.cpp

HEADERS += \
        mainwindow.h \
    item_grafico.h \
    movimiento.h \
    objeto_mov.h \
    intro.h \
    nombre_partida.h \
    data_base.h

FORMS += \
        mainwindow.ui \
    intro.ui \
    nombre_partida.ui \
    data_base.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc
