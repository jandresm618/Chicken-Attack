#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QDialog>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "nombre_partida.h"
#include <QMessageBox>

namespace Ui {
class Data_Base;
}

class Data_Base : public QDialog
{
    Q_OBJECT

public:
    explicit Data_Base(QWidget *parent = nullptr);
    void crearTabladeUsuarios();
    void crearTabladeDatos();
    void crearTabladeRecords();

    void insertarUsuario();
    void insertarDatos();
    void insertarRecord();

    void mostrarUsuarios();
    void mostrarDatos();
    void mostrarRecord();

    bool validarUsuario(QString name,QString psswd);

    bool newLoad;


    ~Data_Base();
private slots:
    void recolectarDatos();

private:
    Ui::Data_Base *ui;
    QSqlDatabase database;
    QString name;
    QString pass;
    QString name_partida;

    Nombre_Partida *window;




    int level;

    int vida;
    int score;
    int cant_jugadores;
    int turno;
    int vida_1,score_1;
    int vida_2,score_2;
    int vida_3,score_3;
    int vida_4,score_4;
    int high_score;


};

#endif // DATA_BASE_H
