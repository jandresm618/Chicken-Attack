#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Se inicializa el contenedor de datos
    datos=new Data_Base;

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
        if(datos->validarUsuario(ngame->name,ngame->password)){
            //Usuario y contraseña validos
            QMessageBox::information(this,"WARNING",  "Usuario y contraseña validos");
        }
        else if(datos->user && !datos->password){
            //Usuario Valido contraseña incorrecta
            QMessageBox::information(this,"WARNING",  "//Usuario Valido contraseña incorrecta");
        }
        else{
            //El usuario no existe
//            if(crearNuevoUsuario())datos->exec();
            QMessageBox::information(this,"WARNING",  "El usuario no existe");
        }
    }
    else{
        //Cargar juego
        nom_partida->setModal(true);
        nom_partida->exec();
    }



    this->show();

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
    connect(serialport,&QTimer::timeout,this,&MainWindow::serialMove);
    connect(this,&MainWindow::shot,this,&MainWindow::disparar);
    time->start(2000);
//        time->start(inicio->time_adEnemys);
    connect(colisiones,&QTimer::timeout,this,&MainWindow::collisiones);
    colisiones->start(30);
    serialport->start(500);
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
                cargarEscena(100,0);
//        cargarEscena(datos->vida,datos->score);
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
    score=0;
    blood=100;
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
    serialport=new QTimer;

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
        //Es bala
        if(obj->x()>limit_x ){
            // Bala sale del cuadro sin destino
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
        }
        else if(obj->x()<50){
            // NO EXISTE ESTE CASO

            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;

        }
        else if(obj->y()>limit_y | obj->y()<0) {
//            qDebug()<<"Limte Superior e inferior";
            scene->removeItem(obj);
            bullets.removeOne(obj);
            delete obj;
        }
    }
    else{
        //Es Pollo
        if(obj->x()>limit_x ){
            //ENEMIGO SALE DEL LIMITE DERECHO (NO EXISTE ESTE CASO)
            scene->removeItem(obj);
            enemys.removeOne(obj);
            delete obj;
            qDebug()<<"Eliminado 2";
        }
        else if(obj->x()<50){

            //ENEMIGO SALE DEL LIMITE IZQUIERDO(RESTA VIDA)
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
//            qDebug()<<"eliminado";
            scene->removeItem(enem);
            scene->removeItem(bull);
            enemys.removeOne(enem);
            bullets.removeOne(bull);
            delete enem;
            delete bull;
            emit incrementarPuntaje(1.3);
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

bool MainWindow::crearNuevoUsuario()
{
    bool crear;
    QMessageBox msgBox;
    msgBox.setWindowTitle("WARNING");
    msgBox.setText("El usuario ingresado no se ha encontrado, ¿Desea crear uno nuevo?");
    msgBox.setTextFormat(Qt::RichText);
    QPushButton *exitButton = msgBox.addButton(tr("EXIT"), QMessageBox::ActionRole);
    QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);

    msgBox.exec();

    if (msgBox.clickedButton() == exitButton) {
        // nuevo
        crear=true;
    } else {
        // No nuevo
        crear=false;
    }
    return crear;
}

void MainWindow::collisiones()
{

    foreach(Objeto_mov *bull, this->bullets){
        foreach(Objeto_mov *enem,this->enemys){
//            if(bull->collidingItems().empty())qDebug()<<"VACIOO";
//            if(enem->collidingItems().empty())qDebug()<<"VACIOO";
            if(!bullets.empty()& !enemys.empty()){
                eliminacionPor_Colision(bull,enem);
//                emit moreScore(0.1);
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
    foreach(Objeto_mov *pollos, enemys){
        pollos->pause();
    }
    msgBox.exec();
    if (msgBox.clickedButton() == continuar) {
        // continuar
        connect(this,&MainWindow::shot,this,&MainWindow::disparar);
        time->start(2000);
        foreach(Objeto_mov *pollos, enemys){
            pollos->continuee();
        }
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
