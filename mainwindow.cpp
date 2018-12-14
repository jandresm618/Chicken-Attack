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

    datos=new Data_Base;
    datos->setModal(true);
    datos->exec();
    datos->newLoad=inicio->newLoad;

    nom_partida=new Nombre_Partida;
    nom_partida->setModal(true);
    nom_partida->exec();

    serialInit();


    startGame(1);



}

void MainWindow::cargarJuego()
{
    //estatic->level_n,nombres, vida, score
    //cant jugadores,
    //Todos los connect
    //Opcional path de imagenes o escenarios

    connect(this,&MainWindow::restarVida,this,&MainWindow::lessLife);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->start(2000);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
//        time->start(inicio->time_adEnemys);
    colisiones->start(30);
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

void MainWindow::startGame(int cant)
{
    QString d;
    if(cant==1){
        this->showFullScreen();
        cargarEscena(datos->vida,datos->score);
        QMessageBox::information(this,"TURNO "+d.number(cont),  "PLAYER "+d.number(cont));
        cargarJuego();
    }
}

void MainWindow::endGame()
{
    QString d;
    cont++;
    eliminarEscena();
    if(cont==2){
        startGame(1);
        datos->score_1=score;
    }
    else if(cont==3){
        datos->score_2=score;
        if(datos->score_1>datos->score_2){
            QMessageBox::information(this,"WINNER ",  "EL GANADOR ES EL JUGADOR "+d.number(1));
        }
        else{
            QMessageBox::information(this,"WINNER ",  "EL GANADOR ES EL JUGADOR "+d.number(2));
        }
        this->close();
    }

}
void MainWindow::cargarEscena(int vida, int puntaje)
{
    limit_x=1150;limit_y=770;
    int pos_mario_x=100, pos_mario_y=400;
    int pos_mira_x=limit_x/2, pos_mira_y=limit_y/2;
    if(cont==1){
        blood=datos->vida_1; score=datos->score_1;
    }
    if(cont==2){
        blood=datos->vida_2; score=datos->score_2;
    }
    porc=inicio->porcent;
    ui->progressBar->setValue(blood);
    ui->lcdNumber->display(score);
    //estatico ->Pos Mario, Pos rocas, pos mira, posiciones de salida de enemigos;
    //variable -> blood, score, cant_enemys(en caso de hacerlo), QList pos enemys(*), level_values
    ui->graphicsView->setFixedSize(limit_x,limit_y);
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,limit_x,limit_y);
    ui->graphicsView->setScene(scene);

    mario=new Item_Grafico(QString(":/imagenes/señor1.png"),pos_mario_x,pos_mario_y);
    mira=new Item_Grafico(QString(":/imagenes/mira1.png"),pos_mira_x,pos_mira_y);

    time=new QTimer;
    time_game=new QTimer;
    colisiones=new QTimer;

    scene->addItem(mario);
    scene->addItem(mira);


    mira->setFlags(QGraphicsItem::ItemIsFocusable);
    mira->setFocus();



}
void MainWindow::eliminarEscena()
{
    scene->removeItem(mario);
    scene->removeItem(mira);
    delete  mario;
    delete mira;
    delete scene;
    bullets.clear();
    enemys.clear();
    disconnect(this,&MainWindow::restarVida,this,&MainWindow::lessLife);
    disconnect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
//    time->start(escala);
    disconnect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    time->stop();
    colisiones->stop();
}

void MainWindow::eliminacionPor_Limite(Objeto_mov *obj)
{
    if(obj->getId()){
        if(obj->x()>limit_x ){
            scene->removeItem(obj);
            bullets.removeOne(obj);
//            delete obj;
            qDebug()<<"Eliminado 1 ";
        }
        else if(obj->x()<50){
            //
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;

        }
        else if(obj->y()>limit_y | obj->y()<0) {
            qDebug()<<"Limte Superior e inferior";
            scene->removeItem(obj);
            bullets.removeOne(obj);
//            delete obj;
        }
    }
    else{
        if(obj->x()>limit_x ){
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            qDebug()<<"Eliminado 2";
        }
        else if(obj->x()<50){
            //
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            emit restarVida();
        }
        else if(obj->y()>limit_y | obj->y()<0) {
            qDebug()<<"Limte Superior e inferior";
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
        }
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
            emit incrementarPuntaje(0.3);
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

void MainWindow::lessLife()
{
    blood-=100/4;
    if(blood<=0){
        flag=false;
    }
    ui->progressBar->setValue(blood);
}

void MainWindow::moreScore(float escala)
{
    score+=10*escala;
    ui->lcdNumber->display(score);
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
    bullet=new Objeto_mov(1,200,530,x-50,y-70,inicio->w_object,inicio->h_object);
//    enemy=new Objeto_mov(0);
    bullets.append(bullet);
    scene->addItem(bullet);
}

void MainWindow::agregarEnemigo()
{
    enemy=new Objeto_mov(0,limit_x,limit_y-qrand()%400,600,400,inicio->w_object,inicio->h_object);
    enemys.append(enemy);
    scene->addItem(enemy);
    escala*=0.2;
}
