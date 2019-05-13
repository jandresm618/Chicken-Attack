#ifndef ITEM_GRAFICO_H
#define ITEM_GRAFICO_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>


class Item_Grafico: public QGraphicsItem
{
public:
    Item_Grafico(QString path, int x, int y, int _id);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

    void move();

    void keyPressEvent(QKeyEvent *event);
    int x,y;
    int id;
    int cont=0;

    ~Item_Grafico();
private:
    QPixmap *image;




};

#endif // ITEM_GRAFICO_H
