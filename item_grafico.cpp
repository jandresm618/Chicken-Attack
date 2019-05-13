#include "item_grafico.h"

Item_Grafico::Item_Grafico(QString path, int x, int y,int _id) :x(x),y(y)
{
    image=new QPixmap(path);
    setPos(x,y);
    //true para el regalo y false para el resto
    id=_id;
}

QRectF Item_Grafico::boundingRect() const
{
    if(id==1){
        //Regalo
        return QRectF(0,0,100,100);
    }
    else if (id==2) {
        //Explosion
        return QRectF(0,0,150,150);
    }
    else {
        //Cualquier otro

        return QRectF(0,0,185,350);
    }
}

void Item_Grafico::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),*image,image->rect());
}

void Item_Grafico::move()
{
    y+=10;
    setPos(x,y);
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

Item_Grafico::~Item_Grafico()
{
    delete image;
}
