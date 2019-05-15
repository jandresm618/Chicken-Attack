#include "escena.h"

Escena::Escena(QWidget *parent)
{
    //MOSTAR AQUI EL PUNTAJE
    //NUMERO DE BALAS
    //CANTIDAD DE VIDA

    //AGREGAR REGALOS A LA ESCENA(ITEM GRAFICO QUE SE ,MUEVE HACIA ABAJO)

    desktop=new QDesktopWidget;

    limit_x=desktop->width(); limit_y=desktop->height();
    pos_mario_x=100; pos_mario_y=400;
    pos_mira_x=limit_x/2; pos_mira_y=limit_y/2;    

    life=100; score=0;
//    this->setStyleSheet("border-image: url(:/imagenes/fondo.png)");

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,limit_x,limit_y); // make the scene 800x600 instead of infinity by infinity (default)


    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(limit_x,limit_y);

    mario=new Item_Grafico(QString(":/imagenes/senor1.png"),pos_mario_x,pos_mario_y,0);
    mira=new Item_Grafico(QString(":/imagenes/mira1.png"),pos_mira_x,pos_mira_y,0);


    scene->addItem(mario);
    scene->addItem(mira);


    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();

}

void Escena::loadGame()
{
    //Traer los datos de la tabla
    //setear los datos en la escena y en el mainwindow(setDificultad)
    //Empezar el juego con los datos requeridos
}

void Escena::saveGame()
{
    //Parar el juego
    //Insertar los datos en la tabla
    //Seguir el juego
    qDebug()<<"Game saved";
    continuar();

}

void Escena::disparar(int x, int y,float dt)
{
    bullet=new Objeto_mov(1,200,530,x-50,y-70,80,60,dt);
//    enemy=new Objeto_mov(0);
    bullets.append(bullet);
    scene->addItem(bullet);

}

QGraphicsScene *Escena::getScene() const
{
    return scene;
}

void Escena::setScene(QGraphicsScene *value)
{
    scene = value;
}

int Escena::getLife() const
{
    return life;
}

void Escena::setLife(int value)
{
    life = value;
}

int Escena::getScore() const
{
    return score;
}

void Escena::setScore(int value)
{
    score = value;
}

Item_Grafico *Escena::getMira() const
{
    return mira;
}

void Escena::setMira(Item_Grafico *value)
{
    mira = value;
}

int Escena::getLimit_x() const
{
    return limit_x;
}

void Escena::setLimit_x(int value)
{
    limit_x = value;
}

int Escena::getLimit_y() const
{
    return limit_y;
}

void Escena::setLimit_y(int value)
{
    limit_y = value;
}

void Escena::collisiones()
{    
    explodePlus();
    //Chequea si los objetos en las listas colisionan con los bordes de la escena o entre ellos    
    foreach(Objeto_mov *enem,this->enemys){
        if(eliminacionPor_Limite(enem))return;

        foreach(Objeto_mov *bull, this->bullets){
            if(eliminacionPor_Limite(bull))return;
            if(eliminacionPor_Colision(bull,enem)){
                explosion(bull,enem);
                return;
            }
            foreach(Item_Grafico* gif, gifts){
                if(eliminacionPor_Colision(bull,gif))return;

            }
        }
    }
}

void Escena::explosion(Objeto_mov *enem, Objeto_mov *bull)
{
    int x,y;
    x=enem->x()-40;
//    y=enem->getY()-100;
    y=enem->y()-50;
    explode=new Item_Grafico(":/imagenes/explode.png",x,y,2);
    scene->addItem(explode);
    explosiones.append(explode);
}

void Escena::giftMove()
{
    foreach(Item_Grafico *gif, gifts){
        gif->move();
    }
}

void Escena::pausar()
{
    foreach(Objeto_mov *pollos, enemys){
        pollos->pause();
    }
}

void Escena::continuar()
{
    foreach(Objeto_mov *pollos, enemys){
        pollos->continuee();
    }
}

void Escena::reset()
{
    //eliminar los objetos de la escena
    foreach(Objeto_mov *pollos, enemys){
        delete pollos;

    }
    foreach(Objeto_mov *bull, this->bullets){
        delete  bull;

    }
    foreach(Item_Grafico *gif, this->gifts){
        delete  gif;

    }
    enemys.clear();
    bullets.clear();
    gifts.clear();
    //resetar los valores
    life=100; score=0;

    //begin again
}
bool Escena::eliminacionPor_Limite(Objeto_mov *obj)
{
    bool collides=false;
    if(obj->getId()){
        //Es bala
        if(obj->x()>limit_x ){
            // Bala sale del cuadro sin destino
            qDebug()<<"objeto x: "<<QString::number(obj->x());
            collides=true;
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
        }

        else if(obj->y()<0) {
//            qDebug()<<"Limte Superior e inferior";
            qDebug()<<"BALA SALE POR ENCIMA";
            collides=true;
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
        }
    }
    else{
        //Es Pollo
        if(obj->x()<0){

            qDebug()<<"Restar vida";
            //ENEMIGO SALE DEL LIMITE IZQUIERDO(RESTA VIDA)
//            qDebug()<<"SALE POR LA DERECHA";
            collides=true;
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            life-=10;
        }
        else if((obj->y()>limit_y) || (obj->getY()<0)) {
            qDebug()<<"Limte Superior e inferior";
            qDebug()<<"SALE POR LA DERECHA";
            collides=true;
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;

        }
    }
    return collides;
}

bool Escena::eliminacionPor_Colision(Objeto_mov *bull, Objeto_mov *enem)
{
    bool collides=false;
    //Si la lista de los objetos colisionando NO esta vacia
    if(!enem->collidingItems().empty()){
//        qDebug()<<"Colision";

        //Si estan colisionado           o  estan cercas
        if(enem->collidesWithItem(bull) || clossnes(enem,bull)){
//            qDebug()<<"eliminado";
            //Eliminar de la escena
            scene->removeItem(enem);
            scene->removeItem(bull);

            //Eliminar de las listas
            enemys.removeOne(enem);
            bullets.removeOne(bull);

            //Eliminar de la memoria
            delete enem;
            delete bull;

            //Puntos Felicidades
            score+=10;
            collides=true;
        }
    }
    return collides;

}

bool Escena::eliminacionPor_Colision(Objeto_mov *bull, Item_Grafico *gif)
{
    int rand;
    rand=qrand()%2;
    bool collides=false;
    //Si la lista de los objetos colisionando NO esta vacia
    if(!gif->collidingItems().empty()){
//        qDebug()<<"Colision";

        //Si estan colisionado           o  estan cercas
        if(gif->collidesWithItem(bull) ){
//            qDebug()<<"eliminado";
            //Eliminar de la escena
            scene->removeItem(gif);
            scene->removeItem(bull);

            //Eliminar de las listas
            gifts.removeOne(gif);
            bullets.removeOne(bull);

            //Eliminar de la memoria
            delete gif;
            delete bull;

            //Puntos Felicidades
            if(rand==1)score+=30;
            else life+=10;
            collides=true;
        }
    }
    return collides;

}
void Escena::agregarEnemigo(int _time_move, float dt)
{
    enemy=new Objeto_mov(0,limit_x,limit_y-qrand()%600,600,400,80,60,dt);
    enemy->setTime_move(_time_move);
    enemys.append(enemy);
    scene->addItem(enemy);
    mira->setFocus();
    escala*=0.2;
}

void Escena::agregarRegalo(int _time_move, float dt)
{
    regalo=new Item_Grafico(QString(":/imagenes/GIFT.png"),limit_x-qrand()%600,0,1);
//    regalo->setTime_move(_time_move);
    scene->addItem(regalo);
    gifts.append(regalo);
    escala*=0.2;
}

void Escena::agregarRegalo()
{
    regalo=new Item_Grafico(QString(":/imagenes/pollo2.png"),400,400,1);
    scene->addItem(regalo);
}

bool Escena::clossnes(Objeto_mov *_enem, Objeto_mov *_bullet)
{
    bool close = false;
    if((_enem->getX()>= _bullet->getX() & _enem->getX()<=_bullet->getX()+10)
            | (_enem->getX()<= _bullet->getX() & _enem->getX()>=_bullet->getX()-10)){
        close=true;
    }
    else if((_enem->getY()>= _bullet->getY() & _enem->getY()<=_bullet->getY()+10)
            | (_enem->getY()<= _bullet->getY() & _enem->getY()>=_bullet->getY()-10)){
        close=true;
    }
    return close;
}

void Escena::explodePlus()
{
    foreach(Item_Grafico *expl, explosiones){
        if(expl->cont>20){
            scene->removeItem(expl);
            explosiones.removeOne(expl);
            delete expl;
        }
        else{
            expl->cont++;
        }
    }
}
