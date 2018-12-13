#include "nombre_partida.h"
#include "ui_nombre_partida.h"

Nombre_Partida::Nombre_Partida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nombre_Partida)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(recolectar()));
}

Nombre_Partida::~Nombre_Partida()
{
    delete ui;
}

void Nombre_Partida::recolectar()
{
    if(ui->lineEdit->text()!=""){
        nom_partida.append(ui->lineEdit->text());
            this->close();
    }
    else{
        QMessageBox::information(this,"WARNING",  "Nombre no valido.");
    }
}
