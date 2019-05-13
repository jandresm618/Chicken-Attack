#ifndef OBJETO_MOV_H
#define OBJETO_MOV_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include "movimiento.h"
#include <QGraphicsScene>

class Objeto_mov: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Objeto_mov();
    Objeto_mov(int x, float dt);
    Objeto_mov(bool opc, int x, int y, int xf, int yf, int h, int w, float dt);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

    void movimiento();

    void pause();
    void continuee();

    bool getId() const;
    void setId(bool value);

    float getX();
    float getY();


    void setDt(float dt);
    void setTime_move(int value);
    int getTime_move() const;

    ~Objeto_mov();


private slots:
    void move();

private:
    Movimiento *sim_mov;
    QPixmap *image;
    QTimer *timer_move;
    bool id;
    int h,w;
    float dT=float(0.01);
    int time_move=50;
};

#endif // OBJETO_MOV_H
