#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //CARGAR Y GUARDAR
    //DATOS PARA GUARDAR// MUNICION, VIDA, PUNTAJE, DIFICULTAD, NUMERO DE JUGADORES
    //FUNCION CARGAR ESCENA A PARTIR DE LOS DATOS ANTERIORES
    //O SET DATOS LUEGO DE INICIALIZAR
    //GUARDAR ES INGRESAR LOS DATOS ANTERIORES EN LA BASE DE DATOS


    ui->setupUi(this);
    //Se inicializa el contenedor de datos
    game=new Escena(this);

    ui->graphicsView->setScene(game->getScene());
    ui->graphicsView->setFixedSize(game->getLimit_x(),game->getLimit_y());
    ui->graphicsView->setStyleSheet("border-image: url(:/imagenes/fondo.png)");





    this->showFullScreen();
    this->show();

//    serialInit();


    startGame(1);

}

void MainWindow::setDataBase(const DataBase &datos)
{
    data=new DataBase;

    *data=datos;
}

void MainWindow::setSaveValues()
{
    match_name=data->getName_partida();
    user=data->getUser();
    turno=cont;
    nivel=level;
    vida=game->getLife();
    score_actual=game->getScore();

}

void MainWindow::restart()
{
    eliminarEscena();
    time->stop();
    cargarJuego();
    time->start(time_add);
//    qDebug()<<"time_Add"<<QString::number(time_add);

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

    //Por nivel de dificultad



    //PAra escena

    time=new QTimer;
    time2=new QTimer;
    colisiones=new QTimer;
    serialport=new QTimer;

    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(time2,&QTimer::timeout,this,&MainWindow::agregarRegalo);
    time->start(time_add);
    time2->start(time_gift);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    connect(this,&MainWindow::gameover,this,&MainWindow::game_overed);
    serialport->start(150);
    colisiones->start(50);

}



void MainWindow::endGame()
{
    //?????????????????????????????????
    if(game->getLife()<=0){
        emit gameover();

    }
}

void MainWindow::eliminarEscena()
{
    //?????????????????????????????????
    disconnect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    time->stop();
    disconnect(time2,&QTimer::timeout,this,&MainWindow::agregarRegalo);
    time2->stop();
    disconnect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    disconnect(this,&MainWindow::shot,this,&MainWindow::disparar);
    disconnect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    serialport->stop();
    colisiones->stop();


    game->reset();
    actualizar();
}

void MainWindow::actualizar()
{
    ui->progressBar->setValue(game->getLife());
    ui->lcdNumber->display(game->getScore());
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

void MainWindow::setDificult(int val)
{
    if(val==1){
        //level 1
        level=1;
        time_add=5000;
        time_gift=20000;
        bullets=30;
        dt=0.1;

    }
    else if(val==2){
        //level 2
        level=2;
        time_add=3000;
        time_gift=25000;
        bullets=20;
        dt=0.08;
    }
    else if(val==3){
        //level 3
        level=3;
        time_add=1000;
        time_gift=30000;
        bullets=10;
        dt=0.05;
    }
    qDebug()<<"Dificultad: "<<QString::number(level);


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
        game->disparar(game->getMira()->x,game->getMira()->y,dt);
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
        game->disparar(game->getMira()->x,game->getMira()->y,dt);

    }
}

void MainWindow::collisiones()
{

    game->collisiones();
    actualizar();
    endGame();

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

void MainWindow::game_overed()
{
    //Desea reiniciar?
    //QMessageQuestion
    //if(si) --> inicializa el juego
    //else --> cierra y vuelve al menu
//    this->close();
    if(num_players==1){
        stop();
        QMessageBox::information(this,"JUEGO TERMINADO" ,  " SU PUNTAJE ES "+QString::number(game->getScore()));

        QMessageBox msgBox;
        QPushButton *exitButton = msgBox.addButton(tr("MENU"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);
//        exitButton->setStyleSheet("border-image: url(:/imagenes/EXIT.png);");
//        abortButton->setStyleSheet("border-image: url(:/imagenes/MENU.png);");

        msgBox.exec();

        if (msgBox.clickedButton() == exitButton) {
            // connect
            eliminarEscena();
            this->close();
        } else if (msgBox.clickedButton() == abortButton) {
            // abort
            restart();
        }
    }
    if(cont<num_players){
        //Siguiente turno
        cont++;
        stop();
        QMessageBox::information(this,"TURNO "+QString::number(cont),  "PLAYER "+QString::number(cont));
        restart();
    }
    else {
        stop();
//        game_overed();
        QMessageBox::information(this,"JUEGO TERMINADO" ,  " SU PUNTAJE ES "+QString::number(game->getScore()));


    }
}

void MainWindow::serialMove()
{
    serialRead();
    serialEvent(dir);
    game->giftMove();
    time_gift+=500;
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse moving";
    QMainWindow::mouseMoveEvent(event);

}

void MainWindow::stop()
{
    //?????????????????????????????????
    disconnect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->stop();
    time2->stop();
    game->pausar();

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
    game->disparar(event->x(),event->y(),dt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getNum_players() const
{
    return num_players;
}

void MainWindow::setNum_players(int value)
{
    num_players = value;
    qDebug()<<"Numero de jugadores: "<<QString::number(num_players);
}

void MainWindow::inicioJuego()
{

}

void MainWindow::disparar(int x, int y)
{
    game->disparar(x,y,dt);
    game->agregarRegalo();
}

void MainWindow::agregarEnemigo()
{
    //con estos datos funciona bien, NO EXCELENTE
    game->agregarEnemigo(50,dt);

}

void MainWindow::agregarRegalo()
{
    game->agregarRegalo(50,dt);
    qDebug()<<"Agregando Regalo";
}

void MainWindow::on_actionSave_triggered()
{

    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save  | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    stop();

    if(ret==4194302){
        qDebug()<<"Cancel";
    }
    else if(ret==2048){
        qDebug()<<"SAVE";
        //setear los valores

        data->insertarDatos(match_name,user,turno,nivel,vida,score_actual,num_players,score_2,score_3,score_4);
    }
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
        time->start(time_add);
        game->continuar();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    QPushButton *exitButton = msgBox.addButton(tr("EXIT"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // connect
        eliminarEscena();
        this->close();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
    }
}
