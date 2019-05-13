#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>


class DataBase
{
public:
    DataBase();

    void crearTabladeUsuarios();
    void crearTabladeDatos();
    void crearTabladeRecords();

    void insertarUsuario();
    void insertarUsuario(QString user, QString pass);
    void insertarDatos();
    void insertarDatos(QString name, QString user, int turno, int level, int vida,
                       int score, int num_jug, int score_2,int score_3,int score_4);
    void insertarRecord();
    void insertarRecord(QString name,int high_score);

    void mostrarUsuarios();
    void mostrarDatos();
    void mostrarRecord();

    bool validarUsuario(QString name,QString psswd);
    bool validarMatchName(QString name);

    bool getUser() const;
    bool getPassword() const;

    void setUser(bool value);
    void setPassword(bool value);


    int level;

    bool turno;
    int vida_1,score_1;
    int vida_2,score_2;

    ~DataBase();



    QString getName_partida() const;
    void setName_partida(const QString &value);

private:
    QSqlDatabase database;
    QString name;
    QString pass;
    QString name_partida;

    int high_score;
    bool user, password;

};

#endif // DATABASE_H
