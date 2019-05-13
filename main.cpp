#include "control_usuario.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control_Usuario w;
    w.show();

    return a.exec();
}
