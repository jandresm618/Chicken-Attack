#ifndef CONTROL_USUARIO_H
#define CONTROL_USUARIO_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <database.h>
#include <menu.h>


namespace Ui {
class Control_Usuario;
}

class Control_Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Control_Usuario(QWidget *parent = nullptr);
    void bot_salir_clicked();
    void bot_newUser_clicked();
    void bot_oldUser_clicked();
    void bot_hecho_clicked();


    ~Control_Usuario();

private:
    Ui::Control_Usuario *ui;
    Menu *menu;
    //BOTONES
    QPushButton *exit;
    QPushButton *done;
    QPushButton *new_user;
    QPushButton *known_user;

    //LABELS
    QLabel  *user_label;
    QLabel  *password_label;
    QLabel  *repassword_label;

    //LINE EDIT
    QLineEdit *user_ask;
    QLineEdit *password_ask;
    QLineEdit *repassword_ask;

    //Base de datos
    DataBase *datos;

    //Desktop properties
    QDesktopWidget *desktop;


    int lim_x;
    int lim_y;

    bool newuser;

};

#endif // CONTROL_USUARIO_H
