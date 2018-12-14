#include "objeto_mov.h"

Objeto_mov::Objeto_mov()
{
    sim_mov=new Movimiento(50);
    sim_mov->setPosicion(800,400);
    setPos(800,0);
    image=new QPixmap(":/imagenes/pollo.png");
    movimiento();
}

Objeto_mov::Objeto_mov(int x)
{
    sim_mov=new Movimiento(50);
    sim_mov->setPosicion(x,0);
    setPos(x,0);
    image=new QPixmap(":/imagenes/pollo.png");
    movimiento();
}

Objeto_mov::Objeto_mov(bool opc, int x, int y, int xf, int yf)
{
    if(opc){
//        sim_mov=new Movimiento(opc,x,y,xf,yf);
        sim_mov=new Movimiento(1,0);
        sim_mov->setPosicion(x,y);
        setPos(x,y);
        image=new QPixmap(":/imagenes/mira.png");
        movimiento();
        id=true;// Es BALA
    }
    else{
        sim_mov=new Movimiento(opc,x,y,xf,yf);
        sim_mov->setPosicion(x,y);
        setPos(x,y);
        image=new QPixmap(":/imagenes/pollo1.png");
        movimiento();
        id=false; //Es POLLO
    }
}
QRectF Objeto_mov::boundingRect() const
{
    if(id){
        return QRectF(0,0,50,50);
    }
    else{
        return QRectF(0,0,200,200);
    }
}

void Objeto_mov::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),*image,image->rect());
}

void Objeto_mov::movimiento()
{
    time_move=new QTimer;
    connect(time_move,&QTimer::timeout,this,&Objeto_mov::move);
    time_move->start(80);
}


void Objeto_mov::move()
{
    sim_mov->actualizar(float(0.01));
    setPos(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y());
    //x_lim -> 800, y_limit->600
    if(!id){
            if(sim_mov->getPosicion()->y()>450){
                sim_mov->setVelocidad(sim_mov->getVelocidad()->x(),(sim_mov->getVelocidad()->y())*-1*0.2);
                sim_mov->setPosicion(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y()-15);
            }
            if(sim_mov->getPosicion()->y()<390){
                sim_mov->setVelocidad(sim_mov->getVelocidad()->x(),(sim_mov->getVelocidad()->y())*-1*0.2);
                sim_mov->setPosicion(sim_mov->getPosicion()->x(),sim_mov->getPosicion()->y()+15);
            }
    }
}

bool Objeto_mov::getId() const
{
    return id;
}

void Objeto_mov::setId(bool value)
{
    id = value;
}

Objeto_mov::~Objeto_mov()
{
    delete sim_mov;
    delete image;
    delete time_move;
}
