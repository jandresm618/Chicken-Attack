#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Se inicializa el contenedor de datos
    datos=new Data_Base;
    game=new Escena(this);

    //Recoleccion de datos de usuario
    inicio=new Intro;
    inicio->setModal(true);
    inicio->exec();

    ngame=new NewGame;
    nom_partida=new Nombre_Partida;

    if(inicio->newLoad){
        //Nuevo juego
        ngame->setModal(true);
        ngame->exec();

    }
    else{
        //Cargar juego
        nom_partida->setModal(true);
        nom_partida->exec();
}




    cargarJuego();

    limit_x=1150;limit_y=770;
    ui->graphicsView->setScene(game->getScene());
    ui->graphicsView->setFixedSize(limit_x,limit_y);    


    this->showFullScreen();
    this->show();

//    game->show();

    serialInit();


//    startGame(1);



}

void MainWindow::startGame(int cant)
{
    //Funcion encargada del multijugador
    QString d;
    if(cant==1){
        this->showFullScreen();
        cargarEscena(100,0);
//      cargarEscena(datos->vida,datos->score);
        QMessageBox::information(this,"TURNO "+d.number(cont),  "PLAYER "+d.number(cont));
        cargarJuego();
    }
}
void MainWindow::cargarEscena(int vida, int puntaje)
{
    //Carga la escena
}
void MainWindow::cargarJuego()
{
    //estatic->level_n,nombres, vida, score
    //cant jugadores,
    //Todos los connect
    //Opcional path de imagenes o escenarios


    //PAra escena

    time=new QTimer;
    colisiones=new QTimer;
    serialport=new QTimer;
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    time->start(2000);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    serialport->start(500);
    colisiones->start(30);
//        time->start(inicio->time_adEnemys);

}



void MainWindow::endGame()
{
    //?????????????????????????????????
}

void MainWindow::eliminarEscena()
{
    //?????????????????????????????????
}

void MainWindow::actualizar()
{
    ui->progressBar->setValue(game->getLife());
    ui->lcdNumber->display(game->getScore());
//    score=game->getScore();
//    blood=game->getLife();
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
//        mira->x-=50;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->x-=50;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);

    }
    else if(event->key() == Qt::Key_Right){
//        mira->x+=50;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->x+=50;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
    }
    else if(event->key() == Qt::Key_Up){
//        mira->y-=50;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->y-=50;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
    }
    else if(event->key() == Qt::Key_Down){
//        mira->y+=50;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->y+=50;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
    }
    else if(event->key() == Qt::Key_Space /*&& armaFlag*/){
//        emit shot(mira->x,mira->y);
        game->disparar(game->getMira()->x,game->getMira()->y);
    }

}

void MainWindow::serialEvent(char dir)
{
    if(dir == 'L'){
//        mira->x-=10;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->x-=10;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);

    }
    else if(dir == 'R'){
//        mira->x+=10;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->x+=10;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
    }
    else if(dir == 'U'){
//        mira->y-=10;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->y-=50;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
    }
    else if(dir == 'D'){
//        mira->y+=10;
//        mira->setPos(mira->x,mira->y);
        game->getMira()->x+=10;
        game->getMira()->setPos(game->getMira()->x,game->getMira()->y);
}
    else if(dir == 'S'){
//        emit shot(mira->x,mira->y);
        game->disparar(game->getMira()->x,game->getMira()->y);

    }
}

void MainWindow::collisiones()
{

    game->collisiones();

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
    score+=10;
    ui->lcdNumber->display(score);
}

void MainWindow::serialMove()
{
    serialRead();
    serialEvent(dir);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse moving";
    QMainWindow::mouseMoveEvent(event);

}

void MainWindow::stop()
{
    //?????????????????????????????????
    connect(this,&MainWindow::restarVida,this,&MainWindow::lessLife);
    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->start(2000);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
//        time->start(inicio->time_adEnemys);
    colisiones->start(30);
    serialport->start(500);

}

void MainWindow::guardar()
{
    //Guardar en la base de datos
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"Pressed";
    QMainWindow::mousePressEvent(event);
//    emit shot(event->x(),event->y());
    game->disparar(event->x(),event->y());
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
    game->disparar(x,y);
}

void MainWindow::agregarEnemigo()
{
    game->agregarEnemigo();
}

void MainWindow::on_actionSave_triggered()
{

    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
}

void MainWindow::on_actionPause_triggered()
{
    qDebug()<<"Que pasa mucho mas arriba";
    //Pausar el Juego
    QMessageBox msgBox;
    msgBox.setWindowTitle("PAUSE");
    msgBox.setText("Click to continue");
    QPushButton *continuar = msgBox.addButton(tr("Continue"), QMessageBox::ActionRole);

    qDebug()<<"Que pasa mas arriba";

    disconnect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->stop();

    qDebug()<<"Que pasa";
    game->pausar();
    msgBox.exec();
    if (msgBox.clickedButton() == continuar) {
        // continuar
        connect(this,&MainWindow::shot,this,&MainWindow::disparar);
        time->start(2000);
        game->continuar();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    QPushButton *exitButton = msgBox.addButton(tr("EXIT"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);

    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // connect
        eliminarEscena();
        this->close();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
    }
}
