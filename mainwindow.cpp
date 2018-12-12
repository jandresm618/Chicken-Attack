#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    limit_x=800;
    limit_y=600;
    ui->graphicsView->setFixedSize(limit_x,limit_y);


    cargarEscena();
    cargarJuego();

}

void MainWindow::cargarJuego()
{


    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    time->start(escala);
    colisiones->start(100);
}

void MainWindow::cargarEscena()
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,limit_x,limit_y);
    ui->graphicsView->setScene(scene);

    mario=new Item_Grafico(QString(":/imagenes/mario.png"),50,limit_y-200);
    mira=new Item_Grafico(QString(":/imagenes/mira.png"),limit_x/2,limit_y/2);
//    enemy=new Objeto_mov(0,0,0,20,10);
    time=new QTimer;
    colisiones=new QTimer;
//    enemy=new Objeto_mov(0);
    scene->addItem(mario);
    scene->addItem(mira);
//    scene->addItem(enemy);

    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();
}

void MainWindow::eliminarEscena()
{
    scene->removeItem(mario);
    scene->removeItem(mira);
}

void MainWindow::eliminacionPor_Limite(Objeto_mov *obj)
{
    if(obj->x()>limit_x | obj->x()<0){
        scene->removeItem(obj);
        bullets.removeOne(obj);
        delete obj;
        qDebug()<<"Eliminado";
    }
    else if(obj->y()>limit_y | obj->y()<0) {
        qDebug()<<"Limte Superior e inferior";
        scene->removeItem(obj);
        bullets.removeOne(obj);
        delete obj;
    }
}

void MainWindow::eliminacionPor_Colision(Objeto_mov *bull, Objeto_mov *enem)
{
//    if(!enem->collidingItems().empty()){
//        qDebug()<<"Colision";
//        if(enem->collidesWithItem(bull)){
//            qDebug()<<"eliminado";
////            scene->removeItem(enem);
////            scene->removeItem(bull);
////            enemys.removeOne(enem);
////            bullets.removeOne(bull);
////            delete enem;
////            delete bull;
//        }
//    }
//    if(enem->collidingItems().empty())qDebug()<<"No hay colisiones";
//    if(bull->collidingItems().empty())qDebug()<<"No hay colisiones";
    if(bull->x()==enem->x() && bull->y()==enem->y()){
        qDebug()<<"Colision";
//        scene->removeItem(enem);
//        scene->removeItem(bull);
//        enemys.removeOne(enem);
//        bullets.removeOne(bull);
//        delete enem;
//        delete bull;
    }
}

void MainWindow::collisiones()
{
//    foreach(Objeto_mov *bull, this->bullets){
//        foreach(Objeto_mov *enem,this->enemys){
//            if(bull->collidingItems().empty())qDebug()<<"VACIOO";
//            if(enem->collidingItems().empty())qDebug()<<"VACIOO";
////            eliminacionPor_Limite(enem);
////            eliminacionPor_Limite(bull);
////            if(!bullets.empty()& !enemys.empty()){
////                eliminacionPor_Colision(bull,enem);
////            }
//        }
//    }
    for(int i=0;i<bullets.size();i++){
        for (int j=0;i<enemys.size();i++) {
            if(bullets.at(i)->collidingItems().empty())qDebug()<<"VACIO";
            else qDebug()<<" NO VACIOO";
        }
    }

}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"Mouse moving";
    mira->setPos(event->x(),event->y());
    QMainWindow::mouseMoveEvent(event);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"Pressed";
    QMainWindow::mousePressEvent(event);
    emit shot(event->x(),event->y());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::disparar(int x, int y)
{
    bullet=new Objeto_mov(1,50,400,x-50,y-120);
//    enemy=new Objeto_mov(0);
    bullets.append(bullet);
    scene->addItem(bullet);
//    collidingItems();
}

void MainWindow::agregarEnemigo()
{
    enemy=new Objeto_mov(0,660,rand()%300,600,400);
    enemys.append(enemy);
    scene->addItem(enemy);
    escala*=0.2;
//    collidingItems();
}
