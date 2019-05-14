#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    //HACER BOTON LOAD GAME Y EXIT
    ui->setupUi(this);



    dw=new QDesktopWidget;
    w=dw->width();
    h=dw->height();
    this->setGeometry(0,0,w,h);

    arcade=new QPushButton("",this);
    multiplayer=new QPushButton("",this);
    records=new QPushButton("",this);
    exit=new QPushButton("",this);
    done=new QPushButton("",this);
    load_game=new QPushButton("",this);
    back=new QPushButton("",this);


    dificult_label=new QLabel(QString(""),this);
    title=new QLabel(QString(""),this);
    players_label=new QLabel(QString(""),this);
    match_name_label=new QLabel(QString(""),this);

    match_name_ask=new QLineEdit(this);

    how_many=new QSpinBox(this);
    dificult=new QSpinBox(this);

    records_table=new QTableWidget(this);

    title->hide();
    dificult_label->hide();
    players_label->hide();
    back->hide();
    done->hide();
    how_many->hide();
    records_table->hide();
    dificult->hide();
    match_name_label->hide();
    match_name_ask->hide();


    arcade->setGeometry(dw->width()*3/4-100,dw->height()/5-50,200,100);
    multiplayer->setGeometry(dw->width()*3/4-200,dw->height()*2/5-100,400,90);
    load_game->setGeometry(dw->width()*3/4-130,dw->height()*3/5-140,250,90);
    records->setGeometry(dw->width()*3/4-110,dw->height()*4/5-170,200,90);
    exit->setGeometry(dw->width()*3/4-100,dw->height()-170,150,90);
    done->setGeometry(w*3/4,h*3/4,150,100);

    match_name_label->setGeometry(w*2/4+100,h*2/4+80,250,100);

    match_name_ask->setGeometry(w*3/4,h*2/4+90,150,50);
    title->setGeometry(w*3/4-200,70,150,80);
    records_table->setGeometry(w*3/5,h/4,300,200);

    arcade->setStyleSheet("border-image: url(:/imagenes/ARCADE.png);");
    multiplayer->setStyleSheet("border-image: url(:/imagenes/MULTIPLAYER.png);");
    load_game->setStyleSheet("border-image: url(:/imagenes/LOAD GAME.png);");
    records->setStyleSheet("border-image: url(:/imagenes/RECORDS.png);");
    exit->setStyleSheet("border-image: url(:/imagenes/EXIT.png);");
    done->setStyleSheet("border-image: url(:/imagenes/DONE.png);");

    dificult->setStyleSheet("border-image: url(:/imagenes/index.png);");
    how_many->setStyleSheet("border-image: url(:/imagenes/index.png);");
    records_table->setStyleSheet("border-image: url(:/imagenes/index.png);");
    dificult_label->setStyleSheet("border-image: url(:/imagenes/DIFICULT.png);");
    players_label->setStyleSheet("border-image: url(:/imagenes/PLAYERS.png);");
    match_name_label->setStyleSheet("border-image: url(:/imagenes/MATCH NAME.png);");

    match_name_ask->setStyleSheet("border-image: url(:/imagenes/index.png);");

    connect(arcade,&QPushButton::released,this,&Menu::bot_arcade_clicked);
    connect(multiplayer,&QPushButton::released,this,&Menu::bot_multiplayer_clicked);
    connect(records,&QPushButton::released,this,&Menu::bot_record_clicked);
    connect(exit,&QPushButton::released,this,&Menu::bot_exit_clicked);
    connect(done,&QPushButton::released,this,&Menu::begin);
    connect(load_game,&QPushButton::released,this,&Menu::bot_LoadGame_clicked);
}

void Menu::setDataBase(const DataBase &datos)
{
    data=new DataBase;

    *data=datos;
}


void Menu::begin()
{
    QString name_match=match_name_ask->text();
    //Si Cargar juego fue seleccionado
    qDebug()<<"DONE PRESSED";
    if(load){
        qDebug()<<"LOAD ALREADY";
        //Existe la partida?
        if(!data->validarMatchName(name_match)){
            //DISPONIBLE PARA CARGAR JUEGO
            qDebug()<<"NOMBRE DISPONIBLE PAR CARGAR EL JUEGO";
            data->setName_partida(name_match);
//            setLoadGameValues();
            game=new MainWindow;
            game->setDataBase(*data);
            game->setLoadGameValues();
            game->inicioJuego();
            this->close();
        }
        else {
            QMessageBox::information(this,"WARNING",  "THIS NAME DOESN'T EXIST");
        }
    }
    else {
        //
        if(data->validarMatchName(name_match)){
            data->setName_partida(name_match);
            game=new MainWindow;
            game->setDataBase(*data);
            game->setDificult(dificult->value());
            game->inicioJuego();
    //        setDataBase(*data);
            if(flag){
                //Arcade
                game->setNum_players(1);
            }
            else {
                //Multiplayer
                game->setNum_players(how_many->value());
            }
//            game->show();
            this->close();
        }
        else{
            //QMessageBox que indique que el nombre no esta disponible
            QMessageBox::information(this,"WARNING",  "THIS NAME ALREDY EXIST");
        }
    }
}

Menu::~Menu()
{
    delete ui;
}

void Menu::bot_arcade_clicked()
{
    //DIFICULTAD

    flag=true;

    arcade->hide();
    multiplayer->hide();
    load_game->hide();
    records->hide();
    exit->hide();

    match_name_label->setGeometry(w*2/4,h/3,300,100);
    match_name_ask->setGeometry(w*2/4+300,h/3,300,50);
    match_name_ask->show();
    match_name_label->show();

    dificult_label->show();
    dificult_label->setGeometry(w*2/4,h/2,300,100);

    done->show();

    dificult->setRange(1,3);
    dificult->setGeometry(w*3/4-40,h/2+20,100,50);



    dificult->show();

}

void Menu::bot_multiplayer_clicked()
{
    flag=false;

    arcade->hide();
    multiplayer->hide();
    load_game->hide();
    records->hide();
    exit->hide();

    match_name_label->setGeometry(w*2/4,h/3,300,100);
    match_name_ask->setGeometry(w*2/4+300,h/3,300,50);
    match_name_ask->show();
    match_name_label->show();

    done->show();

    dificult_label->show();
    dificult_label->setGeometry(w*2/4,h/2,300,100);

    dificult->setRange(1,3);
    dificult->setGeometry(w*3/4-40,h/2,100,50);
    dificult->show();

    players_label->setGeometry(w*2/4,h/2+100,300,100);
    players_label->show();

    how_many->setRange(1,4);
    how_many->setGeometry(w*3/4-40,h/2+20+90,100,50);
    how_many->show();

}

void Menu::bot_record_clicked()
{
    int i=0;

    arcade->hide();
    multiplayer->hide();
    load_game->hide();
    records->hide();
    exit->hide();

    done->show();

    QString consulta;
    consulta.append("SELECT * FROM record"
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
    records_table->show();
    title->show();
    title->setStyleSheet("border-image: url(:/imagenes/RECORDS.png);");

    records_table->setRowCount(10);
    records_table->setColumnCount(2);

    while (mostrar.next()) {
        qDebug()<<mostrar.value(1).toByteArray().constData()<<"-->"<<mostrar.value(2).toByteArray().constData();
        records_table->insertRow(i);
        records_table->setItem(i,0,new QTableWidgetItem(mostrar.value(1).toByteArray().constData()));
        records_table->setItem(i,1,new QTableWidgetItem(mostrar.value(2).toByteArray().constData()));
        i++;
    }
}
void Menu::setLoadGameValues()
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
//    cont=turn.toInt();
//    level=dif.toInt();
//    vida=lif.toInt();
//    score=scor.toInt();
//    num_players=players.toInt();
//    score_2=scor_2.toInt();
//    score_3=scor_3.toInt();
//    score_4=scor_4.toInt();
//    setDificult(level);
    qDebug()<<"Datos Cargados";
    qDebug()<<"turno "<<turn.toInt();
    qDebug()<<"nivel "<<dif.toInt();
    qDebug()<<"Vida "<<lif.toInt();
    qDebug()<<"Score "<<scor.toInt();
    qDebug()<<"Num jugadores"<<players.toInt();
    qDebug()<<"Score 2 "<<scor_2.toInt();
    qDebug()<<"Score 3 "<<scor_3.toInt();
    qDebug()<<"Score 4 "<<scor_4.toInt();
    qDebug()<<"VS";
    qDebug()<<"turno "<<turn;
    qDebug()<<"nivel "<<dif;
    qDebug()<<"Vida "<<lif;
    qDebug()<<"Score "<<scor;
    qDebug()<<"Num jugadores"<<players;
    qDebug()<<"Score 2 "<<scor_2;
    qDebug()<<"Score 3 "<<scor_3;
    qDebug()<<"Score 4 "<<scor_4;
}
void Menu::bot_LoadGame_clicked(){
    int i=0;
    load=true;
    arcade->hide();
    multiplayer->hide();
    load_game->hide();
    records->hide();
    exit->hide();

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
    records_table->show();
    match_name_ask->show();
    match_name_label->show();
    done->show();

    title->show();
    title->setStyleSheet("border-image: url(:/imagenes/LOAD GAME.png);");


    records_table->setRowCount(10);
    records_table->setColumnCount(2);

    while (mostrar.next()) {
        qDebug()<<mostrar.value(1).toByteArray().constData()<<"-->"<<mostrar.value(2).toByteArray().constData();
        records_table->insertRow(i);
        records_table->setItem(i,0,new QTableWidgetItem(mostrar.value(1).toByteArray().constData()));
        records_table->setItem(i,1,new QTableWidgetItem(mostrar.value(2).toByteArray().constData()));
        i++;
    }

}

void Menu::bot_exit_clicked()
{
    this->close();
}
