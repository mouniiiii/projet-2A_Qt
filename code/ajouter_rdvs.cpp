#include "ajouter_rdvs.h"
#include "ui_ajouter_rdvs.h"

#include "rdv.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "smtp.h"

Ajouter_RDVs::Ajouter_RDVs(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Ajouter_RDVs)
{
    ui->setupUi(this);
    ui->ID_RDV->setValidator(new QIntValidator(1, 999, this)); // controle de saisie
}

Ajouter_RDVs::~Ajouter_RDVs()
{
    delete ui;
}

// Ajout
void Ajouter_RDVs::on_pushButton_2_clicked()
{
    // recuperation des info
    int ID_RDV = ui->ID_RDV->text().toInt();
    QDateTime DATE = ui->Date->dateTime();
    QString CENTRE = ui->centre_box->currentText();

    RDV r(ID_RDV, DATE, CENTRE);

    bool test = r.ajouter();
    //************mailllll
    // Formater le corps du message avec les valeurs saisies
    QString message = QString("Le rendez vous avec l'ID_RDV %1 a été ajouté avec succès.\n"
                              "DATE : %2\n"
                              "CENTRE : %3\n")
            // "MATRICULE : %4\n")
            .arg(r.getID_RDV())
            .arg(r.getDate().toString(Qt::ISODate))
            .arg(r.getCentre());
    // .arg(MATRICULE);

    qDebug() << "id" << r.getID_RDV();
    qDebug() << "date" << r.getDate();
    qDebug() << "centre" << r.getCentre();

    Smtp *smtp = new Smtp("rania.naouar@esprit.tn", "211JFT5407", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("rania.naouar@esprit.tn", "rania.naouar@esprit.tn", "RDV", message);

    //*************

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
