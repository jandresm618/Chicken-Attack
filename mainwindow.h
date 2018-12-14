#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "item_grafico.h"
#include "objeto_mov.h"
#include "data_base.h"
#include "intro.h"
#include "nombre_partida.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    //Arduino
    void serialInit();
    void serialRead();

    //Mover mira
    void keyPressEvent(QKeyEvent *event);
    void serialEvent(char dir);
    //Introduccion del juego
    void startGame(int cant);
    void endGame();
    //
    void cargarJuego();
    void cargarEscena(int vida, int puntaje);
    void eliminarEscena();

    //DO COLLISIO
    void eliminacionPor_Limite(Objeto_mov*obj);
    void eliminacionPor_Colision(Objeto_mov*bull,Objeto_mov*enem);

    ~MainWindow();

private:

    //VARIABLES GRAFICAS
    Ui::MainWindow *ui;
    QSerialPort serial;
    char dir;
    QGraphicsScene *scene;
    Item_Grafico *mario;
    Item_Grafico *mira;
    Objeto_mov *enemy;
    QTimer *time;    
    QTimer *colisiones;
    Objeto_mov *bullet;
    QList<Objeto_mov*> enemys;
    QList<Objeto_mov*> bullets;
    QTimer *time_game; //Para contabilizar el tiempo de juego
    Intro* inicio;
    Nombre_Partida *nom_partida;
    Data_Base *datos;


    //VARIABLES DE INFOMACION
    bool ready; //PAra saber cuando el mainwindow debe cargar el juego
    int limit_x=800,limit_y=600;
    int escala=2000;
    int score=0, blood=0;
    int dif_level;
    int num_players;
    int cant_enemigos;  //A la hora de cargar
    int tiempo_juego;
    QList<int> pos_enemigos;  //A la hora e cargar
    QList<int> scores_;   //puntajes  A LA HORA DE CARGAR
    int num_balas;   //a la hora de cargar
    bool flag;
    float porc;
    int cont=1;
    int score2;

signals:
    void shot(int x, int y);
    void iniciar();
    void incrementarPuntaje(float escala);
    void restarVida();
    void end();

private slots:
    void inicioJuego();
    void disparar(int x, int y);
    void agregarEnemigo();
    void collisiones();
    void lessLife();
    void moreScore(float escala);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
