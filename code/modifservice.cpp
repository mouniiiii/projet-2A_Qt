#include "modifservice.h"
#include "ui_modifservice.h"
#include "QMessageBox"
#include "QSqlQuery"
#include"QSqlQueryModel"
#include "service.h"
#include<QDebug>
Modifservice::Modifservice(int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modifservice)
{
    ui->setupUi(this);
    Service s;
    s.charger(id);
    ui->lineEdit_IDservice->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_PRIXservice->setValidator(new QIntValidator(0,99,this));
    // recuperation des info
    QString ID_SERVICE = QString::number(s.get_idservice());
    QString PRIX = QString::number(s.get_Prix());
    ui->lineEdit_IDservice->setText(ID_SERVICE);
    //ui->lineEdit_TYPEservice->setText(s.get_type());
    ui->lineEdit_PRIXservice->setText(PRIX);

    // rafrechir
    this->repaint();


}

Modifservice::~Modifservice()
{
    delete ui;
}


void Modifservice::on_pushButton_Modifier_clicked()
{

    int ID_SERVICE = ui->lineEdit_IDservice->text().toInt();
   // QString TYPE = ui->lineEdit_TYPEservice->text();
    QString TYPE=ui->comboBox2->currentText();
    float PRIX = ui->lineEdit_PRIXservice->text().toFloat();
    Service s(ID_SERVICE,TYPE,PRIX);

    bool test = s.modifier(ID_SERVICE);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Modification effectuee.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Modification non effectuee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    hide();
}
