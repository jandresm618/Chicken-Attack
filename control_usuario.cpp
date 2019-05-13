#include "control_usuario.h"
#include "ui_control_usuario.h"

Control_Usuario::   Control_Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Usuario)
{
    //HACER BOTON BACK
    //QUE NO SE VEA LA CONTRASEÑA

    ui->setupUi(this);

    desktop=new QDesktopWidget;

    lim_x=desktop->width();
    lim_y=desktop->height();
    this->setGeometry(  0,0,lim_x,lim_y);
    this->setWindowTitle(QString("LOGIN"));
//    setStyleSheet("background-image: url(:/imagenes/intro.png)");


    datos=new DataBase();

    user_label=new QLabel(QString(""),this);
    password_label=new QLabel(QString(""),this);
    repassword_label=new QLabel(QString(""),this);

    user_ask=new QLineEdit("",this);
    password_ask=new QLineEdit("",this);
    repassword_ask=new QLineEdit("",this);

    exit = new QPushButton("",this);
    done = new QPushButton("",this);
    new_user = new QPushButton("",this);
    known_user = new QPushButton("",this);

    exit->setStyleSheet("border-image: url(:/imagenes/EXIT.png);");
    done->setStyleSheet("border-image: url(:/imagenes/DONE.png);");

    new_user->setStyleSheet("border-image: url(:/imagenes/SING UP.png);");
    known_user->setStyleSheet("border-image: url(:/imagenes/LOG IN.png);");

    user_label->setStyleSheet("border-image: url(:/imagenes/NICKNAME.png);");
    password_label->setStyleSheet("border-image: url(:/imagenes/PASSWORD.png);");
    repassword_label->setStyleSheet("border-image: url(:/imagenes/PASSWORD.png);");

    user_ask->setStyleSheet("border-image: url(:/imagenes/index.png);");
    password_ask->setStyleSheet("border-image: url(:/imagenes/index.png);");
    repassword_ask->setStyleSheet("border-image: url(:/imagenes/index.png);");


    exit->hide();
    done->hide();

    new_user->setGeometry(lim_x*3/4-80,lim_y/2,300,110);
    known_user->setGeometry(lim_x*3/4-80,lim_y/2+100,300,100);


//    connect(exit,&QPushButton::clicked,this,&QWidget::close);
    connect(new_user,&QPushButton::clicked,this,&Control_Usuario::bot_newUser_clicked);
    connect(known_user,&QPushButton::clicked,this,&Control_Usuario::bot_oldUser_clicked);
    connect(done,&QPushButton::clicked,this,&Control_Usuario::bot_hecho_clicked);
    connect(exit,&QPushButton::clicked,this,&Control_Usuario::bot_salir_clicked);

}

void Control_Usuario::bot_salir_clicked()
{
    //Boton Salir Presionado
    this->close();
}

void Control_Usuario::bot_newUser_clicked()
{
    //Boton de usuario nuevo presionado
    new_user->hide();
    known_user->hide();

    newuser=true;

    done->show();
    exit->show();

    exit->setGeometry(lim_x*3/5,lim_y*3/5+130,150,90);
    done->setGeometry(lim_x*4/5,lim_y*3/5+130,150,90);



    user_label->setGeometry(lim_x*2/4-20,lim_y/2-110,300,100);
    password_label->setGeometry(lim_x*2/4-20,lim_y/2-10,300,100);
    repassword_label->setGeometry(lim_x*2/4-20,lim_y/2+90,300,100);

    user_ask->setGeometry(lim_x*2/4+280,lim_y/2-100,250,50);
    password_ask->setGeometry(lim_x*2/4+280,lim_y/2,250,50);
    repassword_ask->setGeometry(lim_x*2/4+280,lim_y/2+100,250,50);

    user_label->show();
    password_label->show();
    repassword_label->show();
    user_ask->show();
    password_ask->show();
    repassword_ask->show();
}
void Control_Usuario::bot_oldUser_clicked()
{
    //Boton de usuario conocido presionado
    newuser=false;
    new_user->hide();
    known_user->hide();

    exit->setGeometry(lim_x*3/5,lim_y*3/5+100,200,100);
    done->setGeometry(lim_x*4/5,lim_y*3/5+100,200,100);
    done->show();
    exit->show();


    user_label->setGeometry(lim_x*2/4-60,lim_y/2-110,320,120);
    password_label->setGeometry(lim_x*2/4-60,lim_y/2-10,320,120);

    user_ask->setGeometry(lim_x*2/4+250,lim_y/2-100,250,50);
    password_ask->setGeometry(lim_x*2/4+250,lim_y/2,250,50);

    user_label->show();
    password_label->show();
    user_ask->show();
    password_ask->show();



}

void Control_Usuario::bot_hecho_clicked()
{
    //boton Hecho Presionado
    menu=new Menu;
    bool valid;
    valid=datos->validarUsuario(user_ask->text(),password_ask->text());
    menu->setDataBase(*datos);

    if(newuser){
        //NUEVO USUARIO


        if(!datos->getUser()){
            //Si el usuario no existe se ingresa
            if(password_ask->text()==repassword_ask->text()){
                //Usuario Valido
                datos->insertarUsuario(user_ask->text(),password_ask->text());                
                this->close();
                menu->show();
            }
            else QMessageBox::information(this,"WARNING",  "INCORRECT PASSWORD");
        }
        else
            //El usuario ya existe
            QMessageBox::information(this,"WARNING",  "USER ALREDY EXIST");
    }
    else {
        //VIEJO USUARIO        
        if(valid){
            //Usuario Valido Listo para jugar
            qDebug()<<"LISTOSSSSS";
            this->close();
            menu->show();

        }
        else QMessageBox::information(this,"WARNING",  "INVALID USER");
    }
}

Control_Usuario::~Control_Usuario()
{
    delete ui;
}
