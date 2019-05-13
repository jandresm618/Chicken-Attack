#include "movimiento.h"

Movimiento::Movimiento(int x,float dt) : DT(dt)//Constructor Caida libre
{    
    caidaLibre(x);
}

Movimiento::Movimiento(bool opc, int x, int y, int xf, int yf, float dt) : DT(dt)//Constructor Mov Rectilineo/Parabolico
{
    //MOVIMIENTO PARA LA BALA
    setPosicion(x,y);
    if(opc){
        movRectilineo(xf,yf);
    }
    //MOVIMIENTO PARA EL POLLO
    else{
        movParabolico(xf,yf);
    }

}

Movimiento::Movimiento(int x, int y)
{
    setPosicion(x,y);
    movParabolico();
    setRandomVel();
}
void Movimiento::setPosicion(float _x, float _y)
{
    x=_x; y=_y;
}
void Movimiento::setVelocidad(float _x, float _y)
{
    vx=_x; vy=_y;
}

void Movimiento::setRandomVel()
{
    srand(time_t(nullptr));
    setVelocidad(-1*10+rand()%300,10+rand()%300); //Direccion negativa
}
void Movimiento::setAceleracion(float _x, float _y)
{
    ax=_x; ay=_y;
}
void Movimiento::setWidth(float value)
{
    w = value;
}
void Movimiento::setHigh(float value)
{
    h = value;
}
QPoint* Movimiento::getPosicion()
{
    QPoint *point=new QPoint(int(x),int(y));
    return point;
}
QPoint *Movimiento::getVelocidad()
{
    QPoint *point=new QPoint(int(vx),int(vy));
    return point;
}
QPoint *Movimiento::getAceleracion()
{
    QPoint *point=new QPoint(int(ax),int(ay));
    return point;
}
float Movimiento::getWidth() const
{
    return w;
}
float Movimiento::getHigh() const
{
    return h;
}
void Movimiento::calculaPosicion(float dt)
{
    x = x + vx*dt + (1/2)*ax*float(dt*dt);
    y = y + vy*dt + (1/2)*ay*float(dt*dt);
}
void Movimiento::calculaVelocidad(float dt)
{
    vx = vx + ax*dt;
    vy = vy + ay*dt;
}
void Movimiento::calculaVelInicial(float xf, float yf,float dt)
{
    vx=(xf-x-float(0.5)*ax*float(dt*dt))/dt;
    vy=(yf-y-float(0.5)*ay*float(dt*dt))/dt;
}
void Movimiento::actualizar(float dt)
{
    QString d;
    calculaVelocidad(dt);
    calculaPosicion(dt);
//    qDebug()<<"x"<<d.number(x);
//    qDebug()<<"y"<<d.number(y);
}

void Movimiento::movParabolico()
{
    setAceleracion(0,10);
}

void Movimiento::movParabolico(int x, int y)
{
    setAceleracion(0,-10);
    calculaVelInicial(x,y,DT);
//    setVelocidad(10,-10);
}

void Movimiento::movRectilineo()
{
    setAceleracion(0,0);
}

void Movimiento::movRectilineo(int x, int y)
{
    setAceleracion(0,0);
    calculaVelInicial(x,y,DT);
}

void Movimiento::caidaLibre(int x)
{
    setAceleracion(0,10);
//    setVelocidad(0,10);
    setPosicion(x,0);
}

float Movimiento::getX() const
{
    return x;
}

void Movimiento::setX(float value)
{
    x = value;
}

float Movimiento::getY() const
{
    return y;
}

void Movimiento::setY(float value)
{
    y = value;
}
Movimiento::Movimiento(int tipo, bool direccion)              //Movimiento explicito
{
    DT=0.1;
    srand(unsigned(time(nullptr)));
    if(int(tipo)==0){                      // Movimiento Rectilineo uniforme
        if(direccion){ //Direccion negativa
            setAceleracion(0,0);
            setVelocidad(-50,0);
        }
        else{           //Direccion positiva
            setAceleracion(0,0);
            setVelocidad(50,0);
        }
    }
    else if(int(tipo)==1){                  // Movimiento Parabolico
        if(direccion){ //Direccion Negativa
            setAceleracion(0,10);
            setVelocidad(-(30+rand()%40),30+rand()%40);
        }
        else{           //Direccion Positiva
            setAceleracion(0,10);
            setVelocidad(30+rand()%40,-(30+rand()%40));
        }
    }
    else if(int(tipo)==2){
        setAceleracion(0,10);      //Caida Libre
        setVelocidad(0,5);
    }
    else if(int(tipo)==3){
                                    //Vueloo
    }
}


