#ifndef NOMBRE_PARTIDA_H
#define NOMBRE_PARTIDA_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Nombre_Partida;
}

class Nombre_Partida : public QDialog
{
    Q_OBJECT

public:
    explicit Nombre_Partida(QWidget *parent = nullptr);
    ~Nombre_Partida();

private:
    Ui::Nombre_Partida *ui;
    QString nom_partida;

private slots:
    void recolectar();
};

#endif // NOMBRE_PARTIDA_H
