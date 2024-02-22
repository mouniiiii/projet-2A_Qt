#include "modifier_employes.h"
#include "ui_modifier_employes.h"
#include "employe.h"
#include <QMessageBox>

modifier_employes::modifier_employes(int cin, QWidget *parent) : QMainWindow(parent),
                                                                 ui(new Ui::modifier_employes)
{
    ui->setupUi(this);
    employe emp;
    emp.cahrger_employe(cin);

    // recuperation des info
    QString CIN = QString::number(emp.getCIN());

    ui->lineEdit->setText(CIN);
    ui->lineEdit_2->setText(emp.getNOM_EMP());
    ui->lineEdit_3->setText(emp.getPRENOM_EMP());
    ui->comboBox->setCurrentText(emp.getROLE());
    ui->lineEdit_5->setText(emp.getMDP());
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);

    // ui->dateEdit1->setDate(emp.getdate_ajout());
    //  rafrechir
    this->repaint();
}

modifier_employes::~modifier_employes()
{
    delete ui;
}

void modifier_employes::on_pushButton_clicked()
{

    int CIN = ui->lineEdit->text().toInt();
    QString NOM_EMP = ui->lineEdit_2->text();
    QString PRENOM_EMP = ui->lineEdit_3->text();
    QString ROLE = ui->comboBox->currentText();
    QString MDP = ui->lineEdit_5->text();
    // QDate DATE_RENDEZ_VOUS =ui->dateEdit1->date();

    // employe E (CIN, NOM_EMP , PRENOM_EMP ,ROLE,MDP,DATE_RENDEZ_VOUS );
    employe E(CIN, NOM_EMP, PRENOM_EMP, ROLE, MDP);

    bool test = E.modifier_employe(CIN);

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("modifier"),
                                 QObject::tr(" client modifié .\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    this->hide();
}
