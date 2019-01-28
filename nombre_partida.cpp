#include "nombre_partida.h"
#include "ui_nombre_partida.h"

Nombre_Partida::Nombre_Partida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nombre_Partida)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(recolectar()));
}

void Nombre_Partida::validarUsuario()
{
    QString consulta;
    consulta.append("SELECT * FROM usuarios"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==user){
            name=true;
            if(mostrar.value(2).toByteArray().constData()==password){
                pass=true;
            }
        }
        else {
            QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
        }
    }
}

bool Nombre_Partida::validarNickname()
{
    bool exist=false;
    QString consulta;
    consulta.append("SELECT * FROM datos"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==nom_partida){
            exist=true;
        }
//        else {
//            QMessageBox::information(this,"WARNING",  "NICKNAME NO VALIDO");
//        }
    }
    if(!exist)QMessageBox::information(this,"WARNING",  "NICKNAME NO VALIDO");
    return  exist;
}

Nombre_Partida::~Nombre_Partida()
{
    delete ui;
}

void Nombre_Partida::recolectar()
{
    user.append(ui->lineEdit_2->text());
    password.append(ui->lineEdit_3->text());
    validarUsuario();
    if(ui->lineEdit->text()!=""){
        nom_partida.append(ui->lineEdit->text());

        if(name & pass)this->close();
        else QMessageBox::information(this,"WARNING",  "Usuario y contraseña no validos");
    }
    else{
        QMessageBox::information(this,"WARNING",  "Nombre no valido.");
    }
}
