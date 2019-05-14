#include "objeto_mov.h"

Objeto_mov::Objeto_mov()
{

}

Objeto_mov::Objeto_mov(int x,float dt) :dT(dt)
{
    //Gift
    id=2;
    sim_mov=new Movimiento(x,dt);
    sim_mov->setPosicion(x,0);
    setPos(x,0);
    image=new QPixmap(":/imagenes/gift.png");
    movimiento();
}

Objeto_mov::Objeto_mov(bool opc, int x, int y, int xf, int yf, int h, int w, float dt): h(h),w(w), dT(dt)
{
    if(opc){
        //BULLET
        sim_mov=new Movimiento(opc,x,y,xf,yf,dt);
        sim_mov->setPosicion(x,y);
        image=new QPixmap(":/imagenes/Bala2.png");
        setPos(x,y);
        movimiento();
        id=true;// Es BALA
    }
    else{
        //ENEMY
        sim_mov=new Movimiento(opc,x,y,xf,yf,dt);
//        sim_mov=new Movimiento(1,1);
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
    timer_move=new QTimer;
    connect(timer_move,&QTimer::timeout,this,&Objeto_mov::move);
//    timer_move->start(time_move);
    timer_move->start(100);
}

void Objeto_mov::pause()
{
    timer_move->stop();
}

void Objeto_mov::continuee()
{
    timer_move->start(50);
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
//    sim_mov->actualizar(float(dT));
    sim_mov->actualizar(0.007);
    setPos(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y());

    if(!id){
        if(sim_mov->getPosicion()->y()>650){
            sim_mov->setVelocidad(sim_mov->getVelocidad()->x()*0.7,(sim_mov->getVelocidad()->y())*-1*0.9);
            sim_mov->setPosicion(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y()-15);
        }
        if(sim_mov->getPosicion()->y()<250){
            sim_mov->setVelocidad(sim_mov->getVelocidad()->x()*1.1,(sim_mov->getVelocidad()->y())/**-1*//**0.4*/+100);
            sim_mov->setPosicion(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y()/*+20*/);
        }
    }
}

int Objeto_mov::getTime_move() const
{
    return time_move;
}

void Objeto_mov::setTime_move(int value)
{
    time_move = value;
}

bool Objeto_mov::getId() const
{
    return id;
}

void Objeto_mov::setId(bool value)
{
    id = value;
}

float Objeto_mov::getX()
{
    return sim_mov->getX();
}

float Objeto_mov::getY()
{
    return sim_mov->getX();
}

void Objeto_mov::setDt(float dt)
{
    dT=dt;
}

Objeto_mov::~Objeto_mov()
{
    delete image;
    delete sim_mov;
    delete timer_move;
}
