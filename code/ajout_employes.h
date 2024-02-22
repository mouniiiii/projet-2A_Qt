#ifndef AJOUT_EMPLOYES_H
#define AJOUT_EMPLOYES_H

#include <QMainWindow>
#include "employe.h"

namespace Ui
{
    class ajout_employes;
}

class ajout_employes : public QMainWindow
{
    Q_OBJECT

public:
    explicit ajout_employes(QWidget *parent = nullptr);
    ~ajout_employes();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ajout_employes *ui;
};

#endif // AJOUT_EMPLOYES_H
