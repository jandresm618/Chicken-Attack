#ifndef ESCENA_H
#define ESCENA_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include "item_grafico.h"
#include "objeto_mov.h"



class Escena : public QGraphicsView
{

//signals:
//    void incrementarPuntaje(float escala);
//    void restarVida();
//    void moreScore(float s);

public:
    Escena(QWidget *parent = nullptr);

    void loadGame();   //Ambos actuan con la misma tabla de datos
    void saveGame();

    void disparar(int x, int y, float dt);
    void agregarEnemigo(int _time_move, float dt);
    void agregarRegalo(int _time_move, float dt);
    void agregarRegalo();

    bool clossnes(Objeto_mov *_enem, Objeto_mov *_bullet);
    void explodePlus();

    bool eliminacionPor_Limite(Objeto_mov*obj);
    bool eliminacionPor_Colision(Objeto_mov*bull,Objeto_mov*enem);
    bool eliminacionPor_Colision(Objeto_mov *bull, Item_Grafico *gif);

    void collisiones();
    void explosion(Objeto_mov *enem, Objeto_mov *bull);

    void giftMove();

    void pausar();
    void continuar();
    void reset();

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *value);

    int getLife() const;
    void setLife(int value);

    int getScore() const;
    void setScore(int value);

    Item_Grafico *getMira() const;
    void setMira(Item_Grafico *value);

    int getLimit_x() const;
    void setLimit_x(int value);

    int getLimit_y() const;
    void setLimit_y(int value);

private:
    int limit_x,limit_y; //*
    int pos_mario_x, pos_mario_y;
    int pos_mira_x, pos_mira_y;
    int escala=2000;

    int life,score;    

    QGraphicsScene *scene;  //*
    Item_Grafico *mario;    //*
    Item_Grafico *regalo;    //*
    Item_Grafico *mira;     //*
    Item_Grafico *explode;

    Objeto_mov *enemy;      //*
    QTimer *time;           //* Agregar enemigo
    QTimer *colisiones;     //*
    Objeto_mov *bullet;     //*

    QList<Objeto_mov*> enemys;  //*
    QList<Objeto_mov*> bullets; //*
    QList<Item_Grafico *> gifts; //*
    QList<Item_Grafico *> explosiones; //*
    QDesktopWidget *desktop;

};

#endif // ESCENA_H
