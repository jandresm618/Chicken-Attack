#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QAbstractButton>
#include <QMessageBox>
#include "item_grafico.h"
#include "objeto_mov.h"
#include "escena.h"
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setDataBase(const DataBase &datos);

    void setSaveValues();

    void restart();

    //Arduino
    void serialInit();
    void serialRead();

    void setDificult(int val);
    void setLoadGameValues();

    void showWinner();

    void continuar();
    void stop();

    //Mover mira
    void keyPressEvent(QKeyEvent *event);
    void serialEvent(char dir);
    //Introduccion del juego
    void inicioJuego();
    void startGame(int cant);
    void endGame();
    //
    void cargarJuego();
    void cargarEscena(int vida, int puntaje);
    void eliminarEscena();

    //Actualizacion de datos
    void actualizar();

    //DO COLLISIO
    void eliminacionPor_Limite(Objeto_mov*obj);
    void eliminacionPor_Colision(Objeto_mov*bull,Objeto_mov*enem);

    int getNum_players() const;
    void setNum_players(int value);

    ~MainWindow();


    QString getMatch_name() const;
    void setMatch_name(const QString &value);

private:

    //VARIABLES GRAFICAS
    Ui::MainWindow *ui;
    QSerialPort serial;
    QGraphicsScene *scene;  //*
    QTimer *time;           //* Agregar enemigo
    QTimer *time2;           //* Agregar regalo
    QTimer *colisiones;     //*
    QTimer *serialport;
    QTimer *time_game; //Para contabilizar el tiempo de juego

    Escena *game;

    DataBase *data;



    char dir;

    //VARIABLES DE INFOMACION
    bool ready; //PAra saber cuando el mainwindow debe cargar el juego
    int limit_x,limit_y; //*
    int escala=2000;    //*
    int score=0, blood=0;
    int level;      //*
    int cant_enemigos;  //A la hora de cargar    
    int bullets;   //a la hora de cargar  //*

    //VARIABLES PARA GUARDAR
    QString match_name;
    QString user;
    int turno;
    int nivel;
    int vida=100;
    int score_actual=0;
    int num_players; //para 1 o mas jugadores
    int score_2=0;
    int score_3=0;
    int score_4=0;

    float dt;

    int time_add=2000;
    int time_gift=5000;
    int time_serial=150;
    int time_col=50;

    QList<int> pos_enemigos;  //A la hora e cargar  //*
    QList<int> scores_;   //puntajes  A LA HORA DE CARGAR
    bool flag;
    float porc;
    int cont=1;    

signals:
    void shot(int x, int y);
    void iniciar();
    void death();
    void gameover();
    //APLICAR EN ESCENA
    void incrementarPuntaje(float escala);
    void restarVida();


private slots:
//    void inicioJuego();
    void disparar(int x, int y);
    void agregarEnemigo();
    void agregarRegalo();
    void collisiones();
    void lessLife();
    void moreScore(float escala);

    void game_overed();
    void serialMove();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void guardar();
    void on_actionSave_triggered();
    void on_actionPause_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
