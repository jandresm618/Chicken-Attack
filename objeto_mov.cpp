#include "objeto_mov.h"

Objeto_mov::Objeto_mov()
{

}

Objeto_mov::Objeto_mov(int x)
{
    sim_mov=new Movimiento(50);
    sim_mov->setPosicion(x,0);
    setPos(x,0);
    image=new QPixmap(":/imagenes/pollo.png");
    movimiento();
}

Objeto_mov::Objeto_mov(bool opc, int x, int y, int xf, int yf, int h, int w): h(h),w(w)
{
    if(opc){
        sim_mov=new Movimiento(opc,x,y,xf,yf);
        sim_mov->setPosicion(x,y);
        image=new QPixmap(":/imagenes/Bala2.png");
        setPos(x,y);
        movimiento();
        id=true;// Es BALA
    }
    else{
        sim_mov=new Movimiento(opc,x,y,xf,yf);
        sim_mov->setPosicion(x,y);
        image=new QPixmap(":/imagenes/pollo2.png");
        setPos(x,y);
        movimiento();
        id=false; //Es POLLO
    }
}
QRectF Objeto_mov::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Objeto_mov::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),*image,image->rect());
}

void Objeto_mov::movimiento()
{
    time_move=new QTimer;
    connect(time_move,&QTimer::timeout,this,&Objeto_mov::move);
    time_move->start(50);
}

//void Objeto_mov::collides()
//{
////    qDebug()<<"verificando colisiones";
//    QList<QGraphicsItem*> items=collidingItems();
////    if(items.empty())qDebug()<<"vacio";
//    for(int i=0;i<items.size();i++){
//        qDebug()<<"No vacio";
//        if(typeid(items.at(i))==typeid (Item_Grafico)){
//            qDebug()<<"Colision";
//        }
//        else if(typeid(items.at(i))==typeid (Objeto_mov)){
//            qDebug()<<"Colision1";
//        }
//    }
//}

void Objeto_mov::move()
{
    sim_mov->actualizar(float(0.01));
    setPos(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y());
    //x_lim -> 800, y_limit->600
//    if(sim_mov->getPosicion()->x()>800 | sim_mov->getPosicion()->y()>600){
//        delete this;
//    }
//    if(sim_mov->getPosicion()->x()<0 | sim_mov->getPosicion()->y()<0){
//        delete this;
//    }
    if(sim_mov->getPosicion()->y()>650){
        sim_mov->setVelocidad(sim_mov->getVelocidad()->x()*0.2,(sim_mov->getVelocidad()->y())*-1*0.5);
        sim_mov->setPosicion(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y()-15);
    }
//    collides();
}

bool Objeto_mov::getId() const
{
    return id;
}

void Objeto_mov::setId(bool value)
{
    id = value;
}
