#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "item_grafico.h"
#include "objeto_mov.h"
#include "database.h"
#include "intro.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //INTRODUCCION DEL JUEGO (QWIDGET)

    //MANEJO DE LA BASE DE DATOS  (CARGAR GUARDAR CON SQLITE)

    //MOSTRAR MENSAJES EN LA VENTANA ACTUAL




    ////CARGAR JUEGO

    void cargarJuego();
    void cargarEscena();

    ~MainWindow();

private:

    //VARIABLES GRAFICAS
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Item_Grafico *mario;
    Item_Grafico *mira;
    Objeto_mov *enemy;
    QTimer *time;    
    Objeto_mov *bullet;
    QList<Objeto_mov*> enemys;
    QList<Objeto_mov*> bullets;
    QTimer *time_game; //Para contabilizar el tiempo de juego
    Intro* inicio;


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

signals:
    void shot(int x, int y);
    void iniciar();

private slots:
    void inicioJuego();
    void disparar(int x, int y);
    void agregarEnemigo();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
