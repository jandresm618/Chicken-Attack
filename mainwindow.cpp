
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    limit_x=2000;
    limit_y=800;
    ui->graphicsView->setFixedSize(limit_x,limit_y);

    serialInit();

    cargarEscena();
    cargarJuego();

}

void MainWindow::cargarJuego()
{


    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    time->start(escala);
    colisiones->start(10);
}
void MainWindow::serialInit()
{
    serial.setPortName("/dev/ttyACM0"); //Poner el nombre del puerto, probablemente no sea COM3

    qDebug()<<"Serial init"<<"++++++++++++++++++++"<<endl;

    if(serial.open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!serial.setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
            qDebug()<<serial.errorString();

        if(!serial.setDataBits(QSerialPort::Data8))
            qDebug()<<serial.errorString();

        if(!serial.setParity(QSerialPort::NoParity))
            qDebug()<<serial.errorString();

        if(!serial.setStopBits(QSerialPort::OneStop))
            qDebug()<<serial.errorString();

        if(!serial.setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<serial.errorString();

        qDebug()<<"Serial ok"<<endl;
    }else{
        qDebug()<<"Serial ttyACM0 not opened. Error: "<<serial.errorString();
    }
}

void MainWindow::serialRead(){


    serial.read(&dir,1); //Leer toda la línea que envía arduino
    /*if(dir!=0){

        cout<<dir<<"************+"<<endl;

    }*/
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        mira->x-=50;
        mira->setPos(mira->x,mira->y);


    }
    else if(event->key() == Qt::Key_Right){
        mira->x+=50;
        mira->setPos(mira->x,mira->y);
    }
    else if(event->key() == Qt::Key_Up){
        mira->y-=50;
        mira->setPos(mira->x,mira->y);
    }
    else if(event->key() == Qt::Key_Down){
        mira->y+=50;
        mira->setPos(mira->x,mira->y);
    }
    else if(event->key() == Qt::Key_Space /*&& armaFlag*/){
        disparar(mira->x,mira->y);
    }

}

void MainWindow::serialEvent(char dir)
{
    if(dir == 'L'){
        mira->x-=10;
        mira->setPos(mira->x,mira->y);

    }
    else if(dir == 'R'){
        mira->x+=10;
        mira->setPos(mira->x,mira->y);
    }
    else if(dir == 'U'){
        mira->y-=10;
        mira->setPos(mira->x,mira->y);
    }
    else if(dir == 'D'){
        mira->y+=10;
        mira->setPos(mira->x,mira->y);
    }
    else if(dir == 'S'){
        disparar(mira->x,mira->y);

    }

}



void MainWindow::cargarEscena()
{
//    QPixmap *imagen=new QPixmap(":/imagenes/fondo.png");
////    imagen->setDevicePixelRatio(0.5);
////    imagen->size().setHeight(400);
////    imagen->size().setWidth(600);
//    imagen->scaled(600,400);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,limit_x,limit_y);
    ui->graphicsView->setScene(scene);

//    QBrush *img=new QBrush(Qt::white,*imagen);
//    scene->setBackgroundBrush(*img);

    mario=new Item_Grafico(QString(":/imagenes/señor2.png"),50,limit_y-400);
//    mira=new Item_Grafico(QString(":/imagenes/mira.png"),limit_x/2,limit_y/2);
    mira=new Item_Grafico(QString(":/imagenes/mira1.png"),0,0);
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
    if(!enem->collidingItems().empty()){
        qDebug()<<"Colision";
        if(enem->collidesWithItem(bull)){
            qDebug()<<"eliminado";
            scene->removeItem(enem);
            scene->removeItem(bull);
            enemys.removeOne(enem);
            bullets.removeOne(bull);
            delete enem;
            delete bull;
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

void MainWindow::collisiones()
{
    serialRead();
    serialEvent(dir);
    foreach(Objeto_mov *bull, this->bullets){
        foreach(Objeto_mov *enem,this->enemys){
//            if(bull->collidingItems().empty())qDebug()<<"VACIOO";
//            if(enem->collidingItems().empty())qDebug()<<"VACIOO";
            eliminacionPor_Limite(enem);
            eliminacionPor_Limite(bull);
            if(!bullets.empty()& !enemys.empty()){
                eliminacionPor_Colision(bull,enem);
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
    bullet=new Objeto_mov(1,50,limit_y-400,x-50,y-120);
//    enemy=new Objeto_mov(0);
    bullets.append(bullet);
    scene->addItem(bullet);
//    collidingItems();
}

void MainWindow::agregarEnemigo()
{
    enemy=new Objeto_mov(0,limit_x,limit_y-rand()%300,1600,400);
    enemys.append(enemy);
    scene->addItem(enemy);
    escala*=0.2;
//    collidingItems();
}
