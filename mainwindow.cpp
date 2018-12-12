#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setFixedSize(800,600);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,600);
    ui->graphicsView->setScene(scene);

    mario=new Item_Grafico(QString(":/imagenes/mario.png"),50,400);
    mira=new Item_Grafico(QString(":/imagenes/mira.png"),100,100);
    enemy=new Objeto_mov(0,0,0,20,10);
    time=new QTimer;
//    enemy=new Objeto_mov(0);
    scene->addItem(mario);
    scene->addItem(mira);
    scene->addItem(enemy);

    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();

    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    time->start(escala);
}

void MainWindow::cargarJuego()
{

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

void MainWindow::disparar(int x, int y)
{
    bullet=new Objeto_mov(1,50,400,x-50,y-120);
//    enemy=new Objeto_mov(0);
    scene->addItem(bullet);
}

void MainWindow::agregarEnemigo()
{
    enemy=new Objeto_mov(0,800,150+qrand()%300,600,400);
    enemys.append(enemy);
    scene->addItem(enemy);
    escala*=0.2;
}
