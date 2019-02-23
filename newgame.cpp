#include "newgame.h"
#include "ui_newgame.h"


NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
}

void NewGame::validarUsuario(QString name, QString pass)
{
    QString consulta;
    consulta.append("SELECT * FROM usuarios"
                    );
    QSqlQuery mostrar;
    mostrar.prepare(consulta);
    while(mostrar.next()){
        if(mostrar.value(1).toByteArray().constData()==name){
            user=true;
            if(mostrar.value(2).toByteArray().constData()==pass){
                psswd=true;
            }
        }
        else {
            QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
        }
    }
}

NewGame::~NewGame()
{
    delete ui;
}

void NewGame::clicked()
{
    name.append(ui->lineEdit->text());
    password.append(ui->lineEdit_2->text());
    validarUsuario(name,password);
    level=ui->spinBox->value();
    if(user && psswd){
        //usuario existente y contraseña correcta
        this->close();
    }
    else if(!user){
        //Usuario no existe
        this->close();
    }
    else{
        //Usuario existente y contraseña incorrecta
        QMessageBox::information(this,"WARNING",  "CONTRASÑA INVALIDA");
    }
}
