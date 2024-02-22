#include "fidele2.h"
#include "ui_fidele2.h"
#include "service.h"
#include<QDebug>
#include <QMessageBox>
#include "addservice.h"
#include "modifservice.h"
#include "service.h"
#include "messagerie.h"
#include "statservice.h"
#include "lanmessage.h"


fidele2::fidele2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fidele2)
{
    ui->setupUi(this);
    ui->checkBox->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);





}

fidele2::~fidele2()
{
    delete ui;
}

void fidele2::on_checkBox_stateChanged(int arg1)
{

    ui->tableView->setModel(ser.afficher_remise(arg1));



}

void fidele2::on_checkBox_2_stateChanged(int arg1)
{
    ui->tableView->setModel(ser.afficher_remise2(arg1));

}

void fidele2::on_checkBox_3_stateChanged(int arg1)
{
    ui->tableView->setModel(ser.afficher_remise3(arg1));


}



void fidele2::on_checkBox_pressed()
{

}

void fidele2::on_checkBox_toggled(bool checked)
{

}
