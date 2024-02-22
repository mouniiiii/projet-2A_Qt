#include "ajout_employes.h"
#include "ui_ajout_employes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDate>
#include <QDebug>

ajout_employes::ajout_employes(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::ajout_employes)
{
    // CIN
    ui->setupUi(this);
    // cntr sasie cin
    ui->lineEdit_cin->setValidator(new QIntValidator(0, 99999999, this));

    // NOM+PRENOM+MDP
    QRegExp regex("[A-Za-z_]+"); // Définit une expression régulière qui correspond à une lettre majuscule ou minuscule
    QRegExpValidator *validator = new QRegExpValidator(regex, this);
    ui->lineEdit_nom->setValidator(validator);
    ui->lineEdit_prenom->setValidator(validator);
    ui->lineEdit_mdp->setValidator(validator);
    ui->lineEdit_mdp->setEchoMode(QLineEdit::Password);
}

ajout_employes::~ajout_employes()
{
    delete ui;
}
// appel de la methode ajouter
void ajout_employes::on_pushButton_clicked()
{
    // recuperation des info
    int CIN = ui->lineEdit_cin->text().toInt();
    QString NOM_EMP = ui->lineEdit_nom->text();
    QString PRENOM_EMP = ui->lineEdit_prenom->text();
    QString ROLE = ui->comboBox_role->currentText();
    QString MDP = ui->lineEdit_mdp->text();

    employe E(CIN, NOM_EMP, PRENOM_EMP, ROLE, MDP);

    bool test = E.ajouter_employe();

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout effectue.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Ajout non effectue.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);

    this->hide(); // fermer la page
}
