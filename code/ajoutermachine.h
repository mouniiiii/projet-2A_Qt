#ifndef AJOUTERMACHINE_H
#define AJOUTERMACHINE_H

#include <QDialog>


namespace Ui {
class AjouterMachine;
}

class AjouterMachine : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterMachine(QWidget *parent = nullptr);
    ~AjouterMachine();

private slots:
    void on_pushButton_Ajouter_clicked();

private:
    Ui::AjouterMachine *ui;
};

#endif // AJOUTERMACHINE_H
