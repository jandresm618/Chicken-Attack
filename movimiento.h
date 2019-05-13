#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

//#define DT 0.1

#include <QPoint>
#include <QDebug>
#include <math.h>
#include <time.h>
#include <stdlib.h>

class Movimiento
{
public:
    Movimiento();
    Movimiento(bool opc, int x, int y, int xf, int yf, float dt); //1->Rectilineo, 0->Parabolico con destino
    Movimiento(int x, int y);
    Movimiento(int x, float dt);
    Movimiento(int tipo, bool direccion); //Constructor con el tipo y la direccion del movimiento

    void setPosicion(float _x, float _y);   // METODOS SET
    void setVelocidad(float _x, float _y);
    void setRandomVel();
    void setAceleracion(float _x, float _y);
    void setHigh(float value);
    void setWidth(float value);


    QPoint *getPosicion();                  //METODOS GET
    QPoint *getVelocidad();
    QPoint *getAceleracion();
    float getHigh() const;
    float getWidth() const;


    void actualizar(float dt);              //METODO QUE ACTUALIZA LA VELOCIDAD Y LA POCISION EN EL INTERVALO DT

    //TIPOS DE MOVIMIENTO

    void movParabolico();
    void movParabolico(int x, int y);

    void movRectilineo();
    void movRectilineo(int x, int y);

    void caidaLibre(int x);



    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

private:
    float h,w;       //alto y ancho
    float x;
    float y;
    float vx;
    float vy;               //Atributos Fisicos del movimiento
    float ax;
    float ay;

    float DT;
        void calculaPosicion(float dt);         //METODO DE ECUACION CINEMATICA DE POSICION
        void calculaVelocidad(float dt);        //METODO DE ECUACION CINEMATICA DE VELOCIDAD
    void calculaVelInicial (float xf, float yf, float dt);                   //METODO QUE CALCULA EL ANGULO
};

#endif // MOVIMIENTO_H
