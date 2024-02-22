#include "authentification.h"
#include "ui_authentification.h"
#include "employe.h"
#include "ajout_employes.h"


#include <QDialog>
#include <QMessageBox>

authentification::authentification(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::authentification)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

authentification::~authentification()
{
    delete ui;
}

void authentification::on_loginButton_clicked()
{
    // application *a = new application();
    QString nom = ui->lineEdit_username->text();
    QString mdp = ui->lineEdit_password->text();

    QSqlQuery qry;
    if (qry.exec("SELECT * from GESTION_EMPLOYES where NOM_EMP='" + nom + "'"))
    {
        int count = -1;
        while (qry.next())
        {
            count++;
        }
        if (count >= 0)
        {
            QSqlQuery qry1;
            if (qry1.exec("SELECT * from GESTION_EMPLOYES where MDP='" + mdp + "'"))
            {
                int count1 = -1;
                QString role;
                while (qry1.next())
                {
                    role = qry1.value("ROLE").toString();
                    count1++;
                }
                if (count1 >= 0)
                {
                    qDebug() << "Role: " << role;
                    emit loggedIn(role);
                    QMessageBox::information(nullptr, QObject::tr("Gestion-Des-Employes"),
                                             QObject::tr("          Success!\n"
                                                         "Taper sur cancel pour fermer."),
                                             QMessageBox::Cancel);
                    //   a->show();
                    authentification::close();
                }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Gestion-Des-Employes"),
                                          QObject::tr("Votre mot de passe est incorrect!\n"
                                                      "  Taper sur cancel pour fermer."),
                                          QMessageBox::Cancel);
                }
            }
        }
        else if (count < 1)
            QMessageBox::critical(nullptr, QObject::tr("Gestion-Des-Employes"),
                                  QObject::tr(" Votre nom est incorrect!\n"
                                              "Taper sur cancel pour fermer."),
                                  QMessageBox::Cancel);
    }
}

void authentification::on_cancelButton_clicked()
{
    ajout_employes *ajout = new ajout_employes();
        ajout->show();

}
