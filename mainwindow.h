#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "item_grafico.h"
#include "objeto_mov.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void cargarJuego();
    void cargarEscena();
    void eliminarEscena();
    void eliminacionPor_Limite(Objeto_mov*obj);
    void eliminacionPor_Colision(Objeto_mov*bull,Objeto_mov*enem);


    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Item_Grafico *mario;
    Item_Grafico *mira;
    Objeto_mov *enemy;
    QTimer *time;    
    QTimer *colisiones;
    Objeto_mov *bullet;
    QList<Objeto_mov*> enemys;
    QList<Objeto_mov*> bullets;
    int limit_x;
    int limit_y;
    int escala=2000;
    int score;
    int vida;
    int numJugadores;

private slots:
    void disparar(int x, int y);
    void agregarEnemigo();
    void collisiones();

signals:
    void shot(int x, int y);

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
