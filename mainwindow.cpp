#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicio=new Intro;
    inicio->setModal(true);
    inicio->exec();


    this->showFullScreen();
    cargarEscena();
    cargarJuego();



}

void MainWindow::cargarJuego()
{
    //estatic->level_n,nombres, vida, score
    //cant jugadores,
    //Todos los connect
    //Opcional path de imagenes o escenarios
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
//    time->start(escala);
}

void MainWindow::cargarEscena()
{

    int pos_mario_x=50, pos_mario_y=400;
    int pos_mira_x=limit_x/2, pos_mira_y=limit_y/2;
    //estatico ->Pos Mario, Pos rocas, pos mira, posiciones de salida de enemigos;
    //variable -> blood, score, cant_enemys(en caso de hacerlo), QList pos enemys(*), level_values
    ui->graphicsView->setFixedSize(limit_x,limit_y);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,limit_x,limit_y);
    ui->graphicsView->setScene(scene);

    mario=new Item_Grafico(QString(":/imagenes/mario.png"),pos_mario_x,pos_mario_y);
    mira=new Item_Grafico(QString(":/imagenes/mira.png"),pos_mira_x,pos_mira_y);

    time=new QTimer;
    time_game=new QTimer;

    scene->addItem(mario);
    scene->addItem(mira);


    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();



}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse moving";
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

void MainWindow::inicioJuego()
{

}

void MainWindow::disparar(int x, int y)
{
    bullet=new Objeto_mov(1,50,400,x-50,y-120);
//    enemy=new Objeto_mov(0);
    scene->addItem(bullet);
}

void MainWindow::agregarEnemigo()
{
    enemys.append(enemy);
    enemy=new Objeto_mov(0,limit_x,limit_y-qrand()%(3/4)*limit_y,600,400);
    scene->addItem(enemy);
    escala*=0.2;
}
