#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>

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

private:
    Ui::NewGame *ui;
    bool user, psswd;

private slots:
    void clicked();


};

#endif // NEWGAME_H
