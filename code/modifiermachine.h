#ifndef MODIFIERMACHINE_H
#define MODIFIERMACHINE_H

#include <QDialog>

namespace Ui {
class ModifierMachine;
}

class ModifierMachine : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierMachine(int id,QWidget *parent = nullptr);
    ~ModifierMachine();

private slots:
    void on_pushButton_Modifier_clicked();

private:
    Ui::ModifierMachine *ui;
};

#endif // MODIFIERMACHINE_H
