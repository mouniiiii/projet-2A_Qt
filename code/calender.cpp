#include "calender.h"
#include "ui_calender.h"
#include <QTextCharFormat>
#include <QMessageBox>

calender::calender(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::calender)
{
    ui->setupUi(this);
}

calender::~calender()
{
    delete ui;
}

// calendrier

void calender::on_calender_clicked()
{
    // Récupérer les dates de rendez-vous depuis la base de données
    QSqlQuery query;
    query.exec("SELECT DATE_AJOUT FROM GESTION_EMPLOYES");

    // Définir le format de texte pour chaque date de rendez-vous
    QTextCharFormat format;
    format.setBackground(Qt::red);
    format.setForeground(Qt::white);

    while (query.next())
    {
        QDate date = query.value(0).toDate();                // recp valeur 1er colonne
        ui->calendarWidget->setDateTextFormat(date, format); // format afficher la date dans le widget
    }
}

void calender::on_calendarWidget_clicked(const QDate &date)
{

    // Convertir la date sélectionnée en QDateTime à minuit
    QDateTime startOfDay(date, QTime(0, 0, 0));

    // Convertir la date sélectionnée en QDateTime à 23h59
    QDateTime endOfDay(date, QTime(23, 59, 59));

    // Exécuter une requête SQL pour compter le nombre d'employés ajoutés dans la base de données entre les deux QDateTime créés précédemment
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GESTION_EMPLOYES WHERE DATE_AJOUT >= ? AND DATE_AJOUT <= ?");
    query.addBindValue(startOfDay);
    query.addBindValue(endOfDay);
    query.exec();
    query.next();
    int nb_employe_ajoute = query.value(0).toInt();

    // Définir le message et la couleur de la QMessageBox en fonction du nombre d'employés
    QMessageBox msgBox;
    msgBox.setWindowTitle("Nombre d'employés");
    QString message;
    if (nb_employe_ajoute == 0)
    {
        message = "Il n'y a aucun employé ajouté.";
        msgBox.setStyleSheet("background-color: red;");
    }
    else
    {
        message = "Il y a " + QString::number(nb_employe_ajoute) + " employé(s) ajouté(s) ce jour.";
        msgBox.setStyleSheet("background-color: green;");
    }
    msgBox.setText(message);
    msgBox.exec();
}
