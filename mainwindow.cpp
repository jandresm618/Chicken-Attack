#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    //Se inicializa el contenedor de datos
    game=new Escena(this);

    ui->graphicsView->setScene(game->getScene());
    ui->graphicsView->setFixedSize(game->getLimit_x(),game->getLimit_y());
    ui->graphicsView->setStyleSheet("border-image: url(:/imagenes/fondo.png)");

//    data=new DataBase;

    time=new QTimer;
    time2=new QTimer;
    colisiones=new QTimer;
    serialport=new QTimer;

//    data->insertarDatos();
//    data->insertarDatos("arcade","javier",1,1,100,0,1,0,0,0);
//    data->mostrarDatos();

//    data->mostrarUsuarios();
//    data->insertarRecord("mamaste",QString::number(75));
//    data->mostrarRecord();


//    this->showFullScreen();
//    this->show();

////    serialInit();


//    startGame(1);

}

void MainWindow::restart()
{
    stop();
    game->reset();
    actualizar();
//    QMessageBox *msBox = nullptr;
//    msBox->setWindowTitle("RESTART");
//    msBox->setText("CLICK TO PLAY");
//    QPushButton *continua=msBox->addButton(tr("LET'S PLAY"),QMessageBox::ActionRole);
//    if(msBox->clickedButton()==continua)cargarJuego();
    cargarJuego();
    cont=1;
}

void MainWindow::startGame(int cant)
{
    //Funcion encargada del multijugador
    QString d;
    if(cant==1){
        this->showFullScreen();
//      cargarEscena(datos->vida,datos->score);
        QMessageBox::information(this,"TURNO "+d.number(cont),  "PLAYER "+d.number(cont));
        cargarJuego();
    }
}
void MainWindow::inicioJuego(){
    qDebug()<<"Lets play";
    this->showFullScreen();
    this->show();

//    serialInit();
    game->setLife(vida);
    game->setScore(score);

    startGame(1);

}

void MainWindow::cargarJuego()
{
    //PAra escena



    connect(time,&QTimer::timeout,this,&MainWindow::agregarEnemigo);
    connect(time2,&QTimer::timeout,this,&MainWindow::agregarRegalo);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    connect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    connect(this,&MainWindow::gameover,this,&MainWindow::game_overed);
    time->start(time_add);
    time2->start(time_gift);
    serialport->start(time_serial);
    colisiones->start(time_col);

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
    //DIFICULT SETED
    qDebug()<<"DIFICULT SETED";
    if(val==1){
        //level 1
        level=1;
        time_add=5000;
        time_gift=12000;
        bullets=30;
        dt=0.1;

    }
    else if(val==2){
        //level 2
        level=2;
        time_add=3000;
        time_gift=15000;
        bullets=20;
        dt=0.08;
    }
    else if(val==3){
        //level 3
        level=3;
        time_add=1000;
        time_gift=20000;
        bullets=10;
        dt=0.05;
    }
    qDebug()<<"Dificultad: "<<QString::number(level);


}

void MainWindow::setLoadGameValues()
{
    int i=0;
    QString turn;
    QString dif;
    QString lif;
    QString scor;
    QString players;
    QString scor_2;
    QString scor_3;
    QString scor_4;
    QString consulta;
    consulta.append("SELECT * FROM data"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    if(mostrar.exec()){
        qDebug()<<"Se ha mostrado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha mostrado";
        qDebug()<<"ERROR!"<<mostrar.lastError();
    }

    qDebug()<<"ESTOY LLEGANDO POR AQUI";
    while (mostrar.next()) {
        i++;

        qDebug()<<mostrar.value(1).toByteArray().constData()<<"-->"<<data->getName_partida();
        qDebug()<<mostrar.value(2).toByteArray().constData()<<" == "<<data->getName();

        if(data->getName_partida()==mostrar.value(1).toByteArray().constData() && data->getName()==
                mostrar.value(2).toByteArray().constData()){
            qDebug()<<"ENTRANDO AL IF";
            turn=mostrar.value(3).toByteArray().constData();
            dif=mostrar.value(4).toByteArray().constData();
            lif=mostrar.value(5).toByteArray().constData();
            scor=mostrar.value(6).toByteArray().constData();
            players=mostrar.value(7).toByteArray().constData();
            scor_2=mostrar.value(8).toByteArray().constData();
            scor_3=mostrar.value(9).toByteArray().constData();
            scor_4=mostrar.value(10).toByteArray().constData();
        }
    }
    cont=turn.toInt();
    level=dif.toInt();
    vida=lif.toInt();
    score=scor.toInt();
    num_players=players.toInt();
    score_2=scor_2.toInt();
    score_3=scor_3.toInt();
    score_4=scor_4.toInt();
    setDificult(level);
//    setDificult(level);
    qDebug()<<"Datos Cargados";
    qDebug()<<"turno "<<cont;
    qDebug()<<"nivel "<<level;
    qDebug()<<"Vida "<<vida;
    qDebug()<<"Score "<<score;
    qDebug()<<"Num jugadores"<<num_players;
    qDebug()<<"Score 2 "<<score_2;
    qDebug()<<"Score 3 "<<score_3;
    qDebug()<<"Score 4 "<<score_4;
}

void MainWindow::showWinner()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("GAME ENDED");
    msgBox.setText("THE WINNER IS:");
    if(score_2>score_3  || score_4>game->getScore()){
        if(score_2>score_4)msgBox.setInformativeText("PLAYER 1"+QString::number(score_2));
        else msgBox.setInformativeText("PLAYER 3"+QString::number(score_4));
    }
    else {
        if(score_3>game->getScore())msgBox.setInformativeText("PLAYER 2"+QString::number(score_3));
        else msgBox.setInformativeText("PLAYER 4"+QString::number(game->getScore()));
    }

    QPushButton *exitButton = msgBox.addButton(tr("MENU"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);


    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // connect
        this->parentWidget()->show();
        this->close();
        this->deleteLater();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
        restart();
    }
}

void MainWindow::continuar()
{
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->start(time_add);
    time2->start(time_gift);
    serialport->start(time_serial);
    colisiones->start(time_col);
    game->continuar();
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
void MainWindow::setDataBase(const DataBase &datos)
{
    qDebug()<<"DATABASE SETED";

    data=new DataBase;

    *data=datos;
    qDebug()<<"User "<<data->getName();
    qDebug()<<"match name "<<data->getName_partida();
}


void MainWindow::setSaveValues()
{
    qDebug()<<"SAVE VALUES SETED";
    qDebug()<<"User "<<data->getName();
    qDebug()<<"match name "<<data->getName_partida();

    match_name=data->getName_partida();
    user=data->getName();
    turno=cont;
    nivel=level;
    vida=game->getLife();
    score_actual=game->getScore();

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


    if(cont==1)score_2=game->getScore();
    else if (cont==2) score_3=game->getScore();
    else if(cont==3) score_4=game->getScore();

    if(num_players==1){
        stop();        

        QMessageBox msgBox;
        msgBox.setText("GAME ENDED");
        msgBox.setInformativeText("SCORE-->"+QString::number(game->getScore()));
        QPushButton *exitButton = msgBox.addButton(tr("EXIT"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);


        msgBox.exec();

        if (msgBox.clickedButton() == exitButton) {
            // come back to menu
//            this->parentWidget()->show();
            this->close();
            this->deleteLater();
        } else if (msgBox.clickedButton() == abortButton) {
            // abort
            restart();
        }
    }
    if(cont<num_players && num_players!=1){
        //Siguiente turno
        cont++;
//        stop();
        QMessageBox::information(this,"TURNO "+QString::number(cont),  "PLAYER "+QString::number(cont));
        restart();
    }
    else {
        stop();
//        game_overed();        
        showWinner();
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
    serialport->stop();
    colisiones->stop();
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

QString MainWindow::getMatch_name() const
{
    return match_name;
}

void MainWindow::setMatch_name(const QString &value)
{
    match_name = value;
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

void MainWindow::disparar(int x, int y)
{
    game->disparar(x,y,dt);
    game->agregarRegalo();
}

void MainWindow::agregarEnemigo()
{
    //con estos datos funciona bien, NO EXCELENTE
    game->agregarEnemigo(0.01,dt);

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
        setSaveValues();
        data->insertarDatos(match_name,user,turno,nivel,vida,score_actual,num_players,score_2,score_3,score_4);
    }
}

void MainWindow::on_actionPause_triggered()
{    

    //Pausar el Juego
    QMessageBox msgBox;

    msgBox.setWindowTitle("PAUSE");
    msgBox.setText("Click to continue");
    msgBox.setInformativeText("Do you want to restart the game?");
//    msgBox.setStyleSheet("border-image: url(:/imagenes/swamp.png);");
    QPushButton *continua = msgBox.addButton(tr("CONTINUE"), QMessageBox::ActionRole);
    QPushButton *restart = msgBox.addButton(tr("RESTART"), QMessageBox::ActionRole);
    QPushButton *save = msgBox.addButton(tr("SAVE"), QMessageBox::ActionRole);
//    continuar->setStyleSheet("border-image: url(:/imagenes/BACK.png);");
//    restart->setStyleSheet("border-image: url(:/imagenes/RESTART.png);");

    disconnect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->stop();
    time2->stop();
    serialport->stop();
    colisiones->stop();

    game->pausar();
    msgBox.exec();
    if (msgBox.clickedButton() == continua) {
        // continuar
        continuar();
    }
    if (msgBox.clickedButton() == restart) {
        // RESTART

    }
    if (msgBox.clickedButton() == save) {
        // RESTART

    }
}

void MainWindow::on_actionExit_triggered()
{

    QMessageBox msgBox;
    QPushButton *exitButton = msgBox.addButton(tr("EXIT"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(tr("RESTART"),QMessageBox::ActionRole);
    QPushButton *saveButton = msgBox.addButton(tr("SAVE"),QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // connect
        eliminarEscena();
        this->close();
    } else if (msgBox.clickedButton() == abortButton) {
        // abort
        restart();
    }
    else if (msgBox.clickedButton() == saveButton) {
           // save
       }
}
