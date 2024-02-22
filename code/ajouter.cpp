#include "ajouter.h"
#include "ui_ajouter.h"
#include "vehicule.h"
#include "mainwindow.h"
#include <QMessageBox>
Ajouter::Ajouter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ajouter)
{
    ui->setupUi(this);
}

Ajouter::~Ajouter()
{
    delete ui;
}

void Ajouter::on_pushButton_clicked()
{
    QString MATRICULE = ui->lineEdit_matricule->text();
    QString TYPE_V =ui->type_v->itemText(ui->type_v->currentIndex());
    QString MARQUE = ui->lineEdit_marque->text();
    QString N_CHASSIS =ui->lineEdit_chassis->text();

    if(MATRICULE == "" || MARQUE == "" || N_CHASSIS == "")
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Champ vide.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    Vehicule testMatricule;

    if(testMatricule.research_vehicule(MATRICULE)->rowCount()>0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Matricule est deja utiliser\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    QRegularExpression reglementMatricule("^\\d{3}[a-zA-Z]+\\d{4}$");

    if(!reglementMatricule.match(MATRICULE).hasMatch())
    {

        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Format matricule invalide (example du format: 220TUNIS2020).\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    Vehicule v(MATRICULE,TYPE_V,MARQUE,N_CHASSIS);
    v.ajouter_vehicule();


    this->close();
    MainWindow * window = new MainWindow;
    window->show();

}
