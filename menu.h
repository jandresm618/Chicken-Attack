#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <database.h>
#include <QTableWidget>
#include <QDesktopWidget>
#include <QSpinBox>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

    void setDataBase(const DataBase &datos);




    ~Menu();

private slots:
    void bot_arcade_clicked();
    void bot_multiplayer_clicked();
    void bot_record_clicked();
    void bot_exit_clicked();
    void begin();

private:
    Ui::Menu *ui;

    QPushButton *arcade;
    QPushButton *multiplayer;
    QPushButton *load_game;
    QPushButton *records;
    QPushButton *exit;
    QPushButton *done;
    QPushButton *back;

    QLabel *dificult_label;
    QLabel *players_label;
    QLabel *match_name_label;

    QLineEdit *match_name_ask;

    QSpinBox *how_many;
    QSpinBox *dificult;

    QDesktopWidget *dw;

    MainWindow *game;

    QTableWidget *records_table;

    DataBase *data;

    int w,h;
    bool flag;

};

#endif // MENU_H
