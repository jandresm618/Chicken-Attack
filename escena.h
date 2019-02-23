#ifndef ESCENA_H
#define ESCENA_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsScene>
#include "item_grafico.h"
#include "objeto_mov.h"
#include "data_base.h"


class Escena : public QGraphicsView
{

//signals:
//    void incrementarPuntaje(float escala);
//    void restarVida();
//    void moreScore(float s);

public:
    Escena(QWidget *parent = nullptr);

    void disparar(int x, int y);

    void eliminacionPor_Limite(Objeto_mov*obj);
    void eliminacionPor_Colision(Objeto_mov*bull,Objeto_mov*enem);

    void agregarEnemigo();
    void collisiones();

    void pausar();
    void continuar();

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *value);

    int getLife() const;
    void setLife(int value);

    int getScore() const;
    void setScore(int value);

    Item_Grafico *getMira() const;
    void setMira(Item_Grafico *value);

private:
    int limit_x,limit_y; //*
    int pos_mario_x, pos_mario_y;
    int pos_mira_x, pos_mira_y;
    int escala=2000;

    int life,score;

    QGraphicsScene *scene;  //*
    Item_Grafico *mario;    //*
    Item_Grafico *mira;     //*
    Objeto_mov *enemy;      //*
    QTimer *time;           //* Agregar enemigo
    QTimer *colisiones;     //*
    Objeto_mov *bullet;     //*
    QList<Objeto_mov*> enemys;  //*
    QList<Objeto_mov*> bullets; //*
};

#endif // ESCENA_H
