#include "escena.h"

Escena::Escena(QWidget *parent)
{
    limit_x=1150;limit_y=770;
    pos_mario_x=100; pos_mario_y=400;
    pos_mira_x=limit_x/2; pos_mira_y=limit_y/2;    

    life=100; score=0;

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,limit_x,limit_y); // make the scene 800x600 instead of infinity by infinity (default)

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(limit_x,limit_y);

    mario=new Item_Grafico(QString(":/imagenes/señor1.png"),pos_mario_x,pos_mario_y);
    mira=new Item_Grafico(QString(":/imagenes/mira1.png"),pos_mira_x,pos_mira_y);


    scene->addItem(mario);
    scene->addItem(mira);


    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();

//    show();

}

void Escena::disparar(int x, int y)
{
    bullet=new Objeto_mov(1,200,530,x-50,y-70,80,60);
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

void Escena::collisiones()
{

    foreach(Objeto_mov *bull, this->bullets){
        foreach(Objeto_mov *enem,this->enemys){
//            if(bull->collidingItems().empty())qDebug()<<"VACIOO";
//            if(enem->collidingItems().empty())qDebug()<<"VACIOO";
            if(!bullets.empty()& !enemys.empty()){
                eliminacionPor_Colision(bull,enem);
                score++;
            }
            else{
                eliminacionPor_Limite(enem);
                eliminacionPor_Limite(bull);

            }
        }
    }
//    for(int i=0;i<bullets.size();i++){
//        for (int j=0;i<enemys.size();i++) {
//            if(bullets.at(i)->collidingItems().empty())qDebug()<<"VACIO";
//            else qDebug()<<" NO VACIOO";

//        }
//    }

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
void Escena::eliminacionPor_Limite(Objeto_mov *obj)
{
    if(obj->getId()){
        //Es bala
        if(obj->x()>limit_x ){
            // Bala sale del cuadro sin destino
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
            return;
        }
        else if(obj->x()<50){
            // NO EXISTE ESTE CASO

            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
            return;

        }
        else if(obj->y()>limit_y | obj->y()<0) {
//            qDebug()<<"Limte Superior e inferior";
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
            return;
        }
    }
    else{
        //Es Pollo
        if(obj->x()>limit_x ){
            //ENEMIGO SALE DEL LIMITE DERECHO (NO EXISTE ESTE CASO)
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            return;
            qDebug()<<"Eliminado 2";
        }
        else if(obj->x()<50){

            //ENEMIGO SALE DEL LIMITE IZQUIERDO(RESTA VIDA)
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            life--;
            return;
        }
        else if(obj->y()>limit_y | obj->y()<0) {
            qDebug()<<"Limte Superior e inferior";
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            return;
        }
    }
}

void Escena::eliminacionPor_Colision(Objeto_mov *bull, Objeto_mov *enem)
{
    if(!enem->collidingItems().empty()){
        qDebug()<<"Colision";
        if(enem->collidesWithItem(bull)){
//            qDebug()<<"eliminado";
            scene->removeItem(enem);
            scene->removeItem(bull);
            enemys.removeOne(enem);
            bullets.removeOne(bull);
            delete enem;
            delete bull;
            return;
        }
    }
//    if(enem->collidingItems().empty())qDebug()<<"No hay colisiones";
//    if(bull->collidingItems().empty())qDebug()<<"No hay colisiones";
//    if(bull->x()==enem->x() && bull->y()==enem->y()){
//        qDebug()<<"Colision";
//        scene->removeItem(enem);
//        scene->removeItem(bull);
//        enemys.removeOne(enem);
//        bullets.removeOne(bull);
//        delete enem;
//        delete bull;
//    }
}


void Escena::agregarEnemigo()
{
    enemy=new Objeto_mov(0,limit_x,limit_y-qrand()%400,600,400,80,60);
    enemys.append(enemy);
    scene->addItem(enemy);
    escala*=0.2;
}
