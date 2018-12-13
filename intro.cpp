#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(newGame()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(loadGame()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(close()));
}

void Intro::setLevelValues(int level)
{
    switch (level) {
    case 1:
        w_object=100;
        h_object=80;
        time_gifts=2000;
        time_adEnemys=2000;
        break;

    case 2:
        w_object=80;
        h_object=60;
        time_gifts=4000;
        time_adEnemys=1500;
        break;

    case 3:
        w_object=60;
        h_object=40;
        time_gifts=7000;
        time_adEnemys=900;
        break;
    }
}

Intro::~Intro()
{
    delete ui;
}

void Intro::newGame()
{
    //Set Nuevo Juego
}

void Intro::loadGame()
{
    //Set Load Game
}
