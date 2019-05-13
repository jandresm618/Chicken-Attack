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
    nombre_partida.cpp \
    escena.cpp \
    control_usuario.cpp \
    database.cpp \
    menu.cpp

HEADERS += \
        mainwindow.h \
    item_grafico.h \
    movimiento.h \
    objeto_mov.h \
    nombre_partida.h \
    escena.h \
    control_usuario.h \
    database.h \
    menu.h

FORMS += \
        mainwindow.ui \
    nombre_partida.ui \
    control_usuario.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc

DISTFILES += \
    imagenes/fondo.png \
    imagenes/Bala1.png \
    imagenes/Bala2.png \
    imagenes/bullet.png \
    imagenes/cancel.png \
    imagenes/dificult.png \
    imagenes/done.png \
    imagenes/exit.png \
    imagenes/fondo.png \
    imagenes/intro.png \
    imagenes/life.png \
    imagenes/Load.png \
    imagenes/mario.png \
    imagenes/mira.png \
    imagenes/mira1.png \
    imagenes/new.png \
    imagenes/nickgame.png \
    imagenes/nickname.png \
    imagenes/password.png \
    imagenes/pollo.png \
    imagenes/pollo2.png \
    imagenes/score.png \
    imagenes/user.png \
    imagenes/senor1.png \
    imagenes/nick.png
