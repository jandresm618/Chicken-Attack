#include "newgame.h"
#include "ui_newgame.h"

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(recolectar()));
}

void NewGame::validarUsuario(QString name, QString pass)
{
    qDebug()<<"Validndo...";
    int i=0;
    QString consulta;
    consulta.append("SELECT * FROM usuarios"
                    );
    QSqlQuery mostrar;
    if(mostrar.prepare(consulta)){
        qDebug()<<"true";
    }
    else{
        qDebug()<<"false";
    }
    if(mostrar.next()){
        qDebug()<<"hay datos"<<mostrar.value(1);
    }
    else{
        qDebug()<<"No hay datos"<<mostrar.value(1);
    }
    while(mostrar.next()){
        qDebug()<<"Usuario "<<QString::number(i)<<": "<<mostrar.value(1).toByteArray().constData()<<"-"<<mostrar.value(2).toByteArray().constData();
        if(mostrar.value(1).toByteArray().constData()==name){
            user=true;
            if(mostrar.value(2).toByteArray().constData()==pass){
                psswd=true;
            }
        }
        else {
            QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
            user=false;psswd=false;
        }
    }
}

NewGame::~NewGame()
{
    delete ui;
}

bool NewGame::getUser() const
{
    return user;
}

void NewGame::setUser(bool value)
{
    user = value;
}

bool NewGame::getPsswd() const
{
    return psswd;
}

void NewGame::setPsswd(bool value)
{
    psswd = value;
}

void NewGame::recolectar()
{
    name.append(ui->lineEdit->text());
    password.append(ui->lineEdit_2->text());
//    validarUsuario(name,password);
    level=ui->spinBox->value();
//    if(user && psswd){
//        //usuario existente y contraseña correcta
//        qDebug()<<"usuario existente y contraseña correcta";
//        this->close();
//    }
//    else if(!user){
//        //Usuario no existe
//        this->close();
//        qDebug()<<"Usuario no existe";
//    }
//    else{
//        //Usuario existente y contraseña incorrecta
//        QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
//    }
}
