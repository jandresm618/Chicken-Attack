#ifndef OBJETO_MOV_H
#define OBJETO_MOV_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include "movimiento.h"
#include "item_grafico.h"
#include <QGraphicsScene>

class Objeto_mov: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Objeto_mov();
    Objeto_mov(int x);
    Objeto_mov(bool opc, int x, int y, int xf, int yf);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

    void movimiento();

    bool getId() const;
    void setId(bool value);

    ~Objeto_mov();

private slots:
    void move();

private:
    Movimiento *sim_mov;
    QList<Objeto_mov*> enemies;
    QPixmap *image;
    QTimer *time_move;
    bool id;
};

#endif // OBJETO_MOV_H
