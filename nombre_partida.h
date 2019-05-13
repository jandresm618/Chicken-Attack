#ifndef NOMBRE_PARTIDA_H
#define NOMBRE_PARTIDA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class Nombre_Partida;
}

class Nombre_Partida : public QDialog
{
    Q_OBJECT

public:
    explicit Nombre_Partida(QWidget *parent = nullptr);
    QString nom_partida;
    QString user, password;

    void validarUsuario();
    bool validarNickname();

    ~Nombre_Partida();

private:
    Ui::Nombre_Partida *ui;
    bool name,pass;

private slots:
    void recolectar();
};

#endif // NOMBRE_PARTIDA_H
