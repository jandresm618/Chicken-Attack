#include "data_base.h"
#include "ui_data_base.h"

Data_Base::Data_Base(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Data_Base)
{
    ui->setupUi(this);
    QString nombre;
    nombre.append("database_Chicken_Attack.sqlite");
    database= QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nombre);

    if(database.open())qDebug()<<"Base de datos creada.";
    else qDebug()<<"Error al crear la base de datos";

    crearTabladeUsuarios();
    crearTabladeDatos();
    crearTabladeRecords();
//    mostrarUsuarios();


    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(recolectarDatos()));

}

void Data_Base::crearTabladeUsuarios()
{

    //Name-Password
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "contraseña VARCHAR(100)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de usuarios.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de usuarios.";

        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void Data_Base::crearTabladeDatos()
{
    //Name-Vida-Score-Num_jug-turno
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS datos("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "user VARCHAR(100),"
                    "cant_jugadores INTEGER,"
                    "turno INTEGER,"
                    "nivel INTEGER,"
                    "vida_uno INTEGER,"
                    "score_uno INTEGER,"
                    "vida_dos INTEGER,"
                    "score_dos INTEGER,"
                    "vida_tres INTEGER,"
                    "score_tres INTEGER,"
                    "vida_cuatro INTEGER,"
                    "score_cuatro INTEGER"

                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de usuarios.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de usuarios.";
        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void Data_Base::crearTabladeRecords()
{
     //Name-Puntaje
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS record("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "best_score INTEGER"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);
    if(crear.exec()){
        qDebug()<<"Se ha creado la tabla de usuarios.";
    }
    else{
        qDebug()<<"No se ha creado la tabla de usuarios.";
        qDebug()<<"ERROR"<<crear.lastError();
    }
}

void Data_Base::insertarUsuario()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre,"
                    "contraseña"
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+pass+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}
void Data_Base::insertarDatos()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre ,"
                    "user ,"
                    "cant_jugadores ,"
                    "turno ,"
                    "nivel INTEGER,"
                    "vida_uno ,"
                    "score_uno ,"
                    "vida_dos ,"
                    "score_dos ,"
                    "vida_tres ,"
                    "score_tres ,"
                    "vida_cuatro ,"
                    "score_cuatro "
                    ")"
                    "VALUES("
                    "'"+name_partida+"',"
                    "'"+name+"',"
                    "'"+cant_jugadores+"',"
                    "'"+turno+"',"
                    "'"+level+"',"
                    "'"+vida_1+"',"
                    "'"+score_1+"',"
                    "'"+vida_2+"',"
                    "'"+score_2+"',"
                    "'"+vida_3+"',"
                    "'"+score_3+"',"
                    "'"+vida_4+"',"
                    "'"+score_4+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}


void Data_Base::insertarRecord()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre ,"
                    "best_score "
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+high_score+"'"
                    ");");
    QSqlQuery insertar;
    qDebug()<<consulta;
    insertar.prepare(consulta);
    if(insertar.exec()){
        qDebug()<<"Se ha ingresado el usuario correctamente.";
    }
    else {
        qDebug()<<"El usuario no se ha ingresado";
        qDebug()<<"ERROR!"<<insertar.lastError();
    }
}

void Data_Base::mostrarUsuarios()
{
    int i=0;
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
//    ui->tableWidget->setRowCount(0);
//    while (mostrar.next()) {
//        qDebug()<<mostrar.value(1).toByteArray().constData();
//        ui->tableWidget->insertRow(i);
//        ui->tableWidget->setItem(i,0,new QTableWidgetItem("que pasa"));
//    }
}

bool Data_Base::validarUsuario(QString name, QString psswd)
{
    int i=0;
    QString consulta;
    bool exist=false;
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
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==name){
            if(mostrar.value(1).toByteArray().constData()==psswd){
                exist=true;  //Devuelve true si el usuario es correcto
                             //Falso otherwise
            }
        }
        else {
            QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
        }
    }
    return exist;
}
void Data_Base::recolectarDatos()
{
    name.append(ui->lineEdit->text());
    pass.append(ui->lineEdit_2->text());
    level=ui->spinBox->value();
    this->close();
}
Data_Base::~Data_Base()
{
    delete ui;
}
