#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>

namespace Ui {
class DataBase;
}

class DataBase : public QWidget
{
    Q_OBJECT

public:
    explicit DataBase(QWidget *parent = nullptr);

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



    ~DataBase();
private slots:
    void recolectarDatos();

private:
    Ui::DataBase *ui;
    QSqlDatabase database;
    QString name;
    QString pass;
    QString name_partida;

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

#endif // DATABASE_H
