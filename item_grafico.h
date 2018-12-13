#ifndef ITEM_GRAFICO_H
#define ITEM_GRAFICO_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include "objeto_mov.h"

class Item_Grafico: public QGraphicsItem
{
public:
    Item_Grafico(QString path, int x, int y);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

    void keyPressEvent(QKeyEvent *event);

    ~Item_Grafico();

private:
    QPixmap *image;

    int x,y;

signals:
    void shot(int x,int y);
};

#endif // ITEM_GRAFICO_H
