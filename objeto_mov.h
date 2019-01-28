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
    Objeto_mov(int x);
    Objeto_mov(bool opc, int x, int y, int xf, int yf,int h,int w);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

    void movimiento();
//    void collides();

    void pause();
    void continuee();

    bool getId() const;
    void setId(bool value);

    ~Objeto_mov();

private slots:
    void move();

private:
    Movimiento *sim_mov;
    QPixmap *image;
    QTimer *time_move;
    bool id;
    int h,w;
};

#endif // OBJETO_MOV_H
