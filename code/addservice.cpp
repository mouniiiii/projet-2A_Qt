#include "addservice.h"
#include "ui_addservice.h"
#include "QMessageBox"
#include "service.h"
#include<QDebug>
#include<QIntValidator>
#include<QDoubleValidator>

addservice::addservice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addservice)
{
    ui->setupUi(this);
    ui->lineEdit_IDSERVICE->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_PRIX->setValidator(new QIntValidator(0,99,this));
    //ui->lineEdit_TYPE->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
    //ui->lineEdit_TYPE->setValidator(new QRegExpValidator(QRegExp("^(lavage|resteau|visit)$"), this));

}

addservice::~addservice()
{
    delete ui;
}



void addservice::on_pushButton_Ajouter_clicked()
{


    int ID_SERVICE;
    QString TYPE;
    float PRIX;
    QMessageBox messagebox;
    ID_SERVICE=ui->lineEdit_IDSERVICE->text().toInt();
//    TYPE=ui->lineEdit_TYPE->text();
    TYPE=ui->comboBox->currentText();
    PRIX=ui->lineEdit_PRIX->text().toInt();

    Service s(ID_SERVICE,TYPE,PRIX);
    bool test=s.ajouter();
   qDebug()<<test;
    if(test)

    { messagebox.information(nullptr, messagebox.tr("Succès"), messagebox.tr("Ajout effectué"));
    }
    else
        messagebox.critical(nullptr, messagebox.tr("Echec"), messagebox.tr("Ajout non effectué"));







}
