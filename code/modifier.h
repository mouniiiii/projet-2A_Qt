#ifndef MODIFIER_H
#define MODIFIER_H

#include <QMainWindow>
#include "vehicule.h"

namespace Ui {
class modifier;
}

class modifier : public QMainWindow
{
    Q_OBJECT

public:
    explicit modifier(QWidget *parent = nullptr,Vehicule *v = new Vehicule);
    ~modifier();

private slots:
    void on_pushButton_clicked();

private:
    Ui::modifier *ui;
};

#endif // MODIFIER_H
