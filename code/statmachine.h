#ifndef STATMACHINE_H
#define STATMACHINE_H

#include <QDialog>

namespace Ui {
class StatMachine;
}

class StatMachine : public QDialog
{
    Q_OBJECT

public:
    explicit StatMachine(QWidget *parent = nullptr);
    ~StatMachine();

private:
    Ui::StatMachine *ui;
};



#endif // STATMACHINE_H
