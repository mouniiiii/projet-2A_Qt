#ifndef ADDSERVICE_H
#define ADDSERVICE_H
#include<QDebug>
#include <QDialog>

namespace Ui {
class addservice;
}

class addservice : public QDialog
{
    Q_OBJECT

public:
    explicit addservice(QWidget *parent = nullptr);
    ~addservice();
private slots:
    void on_pushButton_Ajouter_clicked();

private:
    Ui::addservice *ui;

};

#endif // ADDSERVICE_H
