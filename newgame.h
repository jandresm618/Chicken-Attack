#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = nullptr);

    void validarUsuario(QString name, QString pass);


    QString name;
    QString password;
    int level;

    ~NewGame();

    bool getUser() const;
    void setUser(bool value);

    bool getPsswd() const;
    void setPsswd(bool value);

private:
    Ui::NewGame *ui;
    bool user, psswd;

private slots:
    void recolectar();


};

#endif // NEWGAME_H
