#ifndef MODIFSERVICE_H
#define MODIFSERVICE_H
#include<QDebug>
#include <QDialog>

namespace Ui {
class Modifservice;
}

class Modifservice : public QDialog
{
    Q_OBJECT

public:
    explicit Modifservice(int id,QWidget *parent = nullptr);
    ~Modifservice();

private slots:
    void on_pushButton_Modifier_clicked();

private:
    Ui::Modifservice *ui;
};

#endif // MODIFSERVICE_H
