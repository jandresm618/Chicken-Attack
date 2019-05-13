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
    players_label=new QLabel(QString(""),this);
    match_name_label=new QLabel(QString(""),this);

    match_name_ask=new QLineEdit(this);

    how_many=new QSpinBox(this);
    dificult=new QSpinBox(this);

    records_table=new QTableWidget(this);

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

    arcade->setStyleSheet("border-image: url(:/imagenes/ARCADE.png);");
    multiplayer->setStyleSheet("border-image: url(:/imagenes/MULTIPLAYER.png);");
    load_game->setStyleSheet("border-image: url(:/imagenes/LOAD GAME.png);");
    records->setStyleSheet("border-image: url(:/imagenes/RECORDS.png);");
    exit->setStyleSheet("border-image: url(:/imagenes/EXIT.png);");
    done->setStyleSheet("border-image: url(:/imagenes/DONE.png);");

    dificult->setStyleSheet("border-image: url(:/imagenes/index.png);");
    how_many->setStyleSheet("border-image: url(:/imagenes/index.png);");
    dificult_label->setStyleSheet("border-image: url(:/imagenes/DIFICULT.png);");
    players_label->setStyleSheet("border-image: url(:/imagenes/PLAYERS.png);");
    match_name_label->setStyleSheet("border-image: url(:/imagenes/MATCH NAME.png);");

    match_name_ask->setStyleSheet("border-image: url(:/imagenes/index.png);");

    connect(arcade,&QPushButton::released,this,&Menu::bot_arcade_clicked);
    connect(multiplayer,&QPushButton::released,this,&Menu::bot_multiplayer_clicked);
    connect(records,&QPushButton::released,this,&Menu::bot_record_clicked);
    connect(exit,&QPushButton::released,this,&Menu::bot_exit_clicked);
    connect(done,&QPushButton::released,this,&Menu::begin);
}

void Menu::setDataBase(const DataBase &datos)
{
    data=new DataBase;

    *data=datos;
}


void Menu::begin()
{
    if(data->validarMatchName(match_name_ask->text())){
        game=new MainWindow;
        game->setDificult(dificult->value());
        setDataBase(*data);
        if(flag){
            //Arcade
            game->setNum_players(1);
        }
        else {
            //Multiplayer
            game->setNum_players(how_many->value());
        }
        game->show();
        this->close();
    }
    else{
        //QMessageBox que indique que el nombre no esta disponible
        QMessageBox::information(this,"WARNING",  "THIS NAME ALREDY EXIST");
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

    QString consulta;
    consulta.append("SELECT * FROM usuarios"
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
    records_table->setStyleSheet("background-color:white");

    records_table->setGeometry(100,100,400,200);
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
