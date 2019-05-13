#include "database.h"

DataBase::DataBase()
{
    QString nombre;
    nombre.append("database_Chicken_Attack.sqlite");
    database= QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(nombre);

    if(database.open())qDebug()<<"Base de datos creada.";
    else qDebug()<<"Error al crear la base de datos";

    crearTabladeUsuarios();
    crearTabladeDatos();
    crearTabladeRecords();
    mostrarUsuarios();

}

void DataBase::crearTabladeUsuarios()
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

void DataBase::crearTabladeDatos()
{
    //Name-Vida-Score-Num_jug-turno
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS datos_juego("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "user VARCHAR(100),"
                    "turno INTEGER,"
                    "nivel INTEGER,"
                    "vida_uno INTEGER,"
                    "score_uno INTEGER,"
                    "num_jugadores INTEGER,"
                    "score_dos INTEGER,"
                    "score_tres INTEGER,"
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

void DataBase::crearTabladeRecords()
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

void DataBase::insertarUsuario()
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

void DataBase::insertarUsuario(QString user, QString passw)
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre,"
                    "contraseña"
                    ")"
                    "VALUES("
                    "'"+user+"',"
                    "'"+passw+"'"
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
void DataBase::insertarDatos()
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre ,"
                    "user ,"
                    "turno ,"
                    "nivel INTEGER,"
                    "vida_uno ,"
                    "score_uno ,"
                    "vida_dos ,"
                    "score_dos "
                    ")"
                    "VALUES("
                    "'"+name_partida+"',"
                    "'"+name+"',"
                    "'"+turno+"',"
                    "'"+level+"',"
                    "'"+vida_1+"',"
                    "'"+score_1+"',"
                    "'"+vida_2+"',"
                    "'"+score_2+"'"
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

void DataBase::insertarDatos(QString name, QString user, int turno, int level, int vida, int score,
                             int num_jug, int score_2, int score_3, int score_4)
{
    QString consulta;
    consulta.append("INSERT INTO usuarios("
                    "nombre ,"
                    "user ,"
                    "turno ,"
                    "nivel INTEGER,"
                    "vida_uno ,"
                    "score_uno ,"
                    "vida_dos ,"
                    "score_dos "
                    ")"
                    "VALUES("
                    "'"+name+"',"
                    "'"+user+"',"
                    "'"+turno+"',"
                    "'"+level+"',"
                    "'"+vida+"',"
                    "'"+score+"',"
                    "'"+num_jug+"',"
                    "'"+score_2+"',"
                    "'"+score_3+"',"
                    "'"+score_4+"',"
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


void DataBase::insertarRecord()
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
void DataBase::insertarRecord(QString name,int high_score)
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
void DataBase::mostrarUsuarios()
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
    while (mostrar.next()) {
        qDebug()<<mostrar.value(1).toByteArray().constData();
        qDebug()<<" == ";
        qDebug()<<mostrar.value(2).toByteArray().constData();
    }
//    ui->tableWidget->setRowCount(0);
//    while (mostrar.next()) {
//        qDebug()<<mostrar.value(1).toByteArray().constData();
//        ui->tableWidget->insertRow(i);
//        ui->tableWidget->setItem(i,0,new QTableWidgetItem("que pasa"));
//    }
}

bool DataBase::validarUsuario(QString name, QString psswd)
{
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
            user=true;
            qDebug()<<"coincide el usuario";
            qDebug()<<mostrar.value(2).toByteArray().constData();
            qDebug()<<"vs";
            qDebug()<<psswd;
            if(mostrar.value(2).toByteArray().constData()==psswd){

                password=true;  //Devuelve true si el usuario es correcto
                             //Falso otherwise
            }
        }
    }
    if(user & password)exist=true;
    qDebug()<<"USUARIO VALIDADO";
    return exist;
}

bool DataBase::validarMatchName(QString name)
{
    //Verifica si en la tabla esta disponible el nombre
    QString consulta;
    bool able=true;
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
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==name){
            able=false;
            qDebug()<<"Nombre no disponible";
        }
    }
    if(able){
        qDebug()<<"Nombre disponible";
        name_partida=name;
    }

    return able;
}


DataBase::~DataBase()
{
}

QString DataBase::getName_partida() const
{
    return name_partida;
}

void DataBase::setName_partida(const QString &value)
{
    name_partida = value;
}

bool DataBase::getUser() const
{
    return user;
}

void DataBase::setUser(bool value)
{
    user = value;
}

bool DataBase::getPassword() const
{
    return password;
}

void DataBase::setPassword(bool value)
{
    password = value;
}
