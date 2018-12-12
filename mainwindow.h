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

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Item_Grafico *mario;
    Item_Grafico *mira;
    Objeto_mov *enemy;
    QTimer *time;    
    Objeto_mov *bullet;
    QList<Objeto_mov*> enemys;
    int escala=2000;

private slots:
    void disparar(int x, int y);
    void agregarEnemigo();

signals:
    void shot(int x, int y);

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
