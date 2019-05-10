#ifndef CONTROL_USUARIO_H
#define CONTROL_USUARIO_H

#include <QDialog>

namespace Ui {
class Control_Usuario;
}

class Control_Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Control_Usuario(QWidget *parent = nullptr);
    ~Control_Usuario();

private:
    Ui::Control_Usuario *ui;
};

#endif // CONTROL_USUARIO_H
