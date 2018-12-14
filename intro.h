#ifndef INTRO_H
#define INTRO_H

#include <QDialog>

namespace Ui {
class Intro;
}

class Intro : public QDialog
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = nullptr);
    void setLevelValues(int level);
    ~Intro();

    bool newLoad;

    int w_object,h_object; //Modificar el tamaño segun el nivel
    int time_gifts;       //Modificar la salida de municiones y vida
    int time_adEnemys;    //Modificar la salida de enemigos

    float porcent;

private slots:
    void newGame();
    void loadGame();
private:
    Ui::Intro *ui;
};

#endif // INTRO_H
