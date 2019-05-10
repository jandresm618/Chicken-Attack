#include "control_usuario.h"
#include "ui_control_usuario.h"

Control_Usuario::Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    ui->setupUi(this);
}

Control_Usuario::~Control_Usuario()
{
    delete ui;
}
