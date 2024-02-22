#include "modifier.h"
#include "ui_modifier.h"
#include "mainwindow.h"
#include <QMessageBox>

modifier::modifier(QWidget *parent,Vehicule *v) :
    QMainWindow(parent),
    ui(new Ui::modifier)
{
    ui->setupUi(this);

    ui->matricule->setText(v->getMatricule());
    ui->marque->setText(v->getMarque());
    ui->n_chassis->setText(v->getN_chassis());
}

modifier::~modifier()
{
    delete ui;
}

void modifier::on_pushButton_clicked()
{


    QString MATRICULE = ui->matricule->text();
    QString TYPE_V =ui->type->itemText(ui->type->currentIndex());
    QString MARQUE = ui->marque->text();
    QString N_CHASSIS =ui->n_chassis->text();

    if(MATRICULE == "" || MARQUE == "" || N_CHASSIS == "")
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Champ vide.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    Vehicule testMatricule;

    if(testMatricule.research_vehicule(MATRICULE)->rowCount()<=0)
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Matricule n'est exist pas\n"
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
    v.modifier_vehicule();


    this->close();
    MainWindow * window =new MainWindow;
    window->show();
}
