#include "item_grafico.h"

Item_Grafico::Item_Grafico(QString path, int x, int y) :x(x),y(y)
{
    image=new QPixmap(path);
    setPos(x,y);
}

QRectF Item_Grafico::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Item_Grafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),*image,image->rect());
}

void Item_Grafico::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        x-=50;
        setPos(qreal(x),qreal(y));


    }
    else if(event->key() == Qt::Key_Right){
        x+=50;
        setPos(qreal(x),qreal(y));
    }
    else if(event->key() == Qt::Key_Up){
        y-=50;
        setPos(qreal(x),qreal(y));
    }
    else if(event->key() == Qt::Key_Down){
        y+=50;
        setPos(qreal(x),qreal(y));
    }
    else if(event->key() == Qt::Key_Space /*&& armaFlag*/){
        qDebug()<<"Disparo";
    }
}
