#include "ajoutermachine.h"
#include "ui_ajoutermachine.h"
#include "machine.h"
#include "QMessageBox"
#include "mainwindow.h"
#include <QIntValidator>

AjouterMachine::AjouterMachine(QWidget *parent) : QDialog(parent),
    ui(new Ui::AjouterMachine)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select ID_SERVICE||'-'||TYPE from GESTION_SERVICES ORDER BY ID_SERVICE");
    ui->comboBox_IDSERVICE->setModel(model);
    ui->lineEdit_IDMACHINE->setValidator(new QIntValidator(0,999,this));
}

AjouterMachine::~AjouterMachine()
{
    delete ui;
}
/*
void AjouterMachine::on_pushButton_Ajouter_clicked()
{
    int id_machine = ui->lineEdit_IDMACHINE->text().toInt();
    QString etat = ui->comboBox_EtatM->currentText();
    QString description = ui->lineEdit_Description_Ajout->text();
    QString id = ui->comboBox_IDSERVICE->currentText();
    int id_service=id.split("-")[0].toInt();

    Machine M(id_machine, etat, description,id_service);
    bool test = M.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
                                 QObject::tr("Ajout effectue.\n"
                                             "Click Ok to exit."),
                                 QMessageBox::Ok);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout"),
                              QObject::tr("Ajout non effectue.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    close();
}
*/
void AjouterMachine::on_pushButton_Ajouter_clicked()
{
    // Get input values
    int id_machine = ui->lineEdit_IDMACHINE->text().toInt();
    QString etat = ui->comboBox_EtatM->currentText();
    QString description = ui->lineEdit_Description_Ajout->text();
    QString id = ui->comboBox_IDSERVICE->currentText();
    int id_service = id.split("-")[0].toInt();

    // Validate input values
    if (id_machine == 0 || description.isEmpty() || id_service == 0) {
        QMessageBox::warning(this, "Warning", "Remplir tous les champs.");
        return;
    }

    // Create a new Machine object and add it to the database
    Machine M(id_machine, etat, description, id_service);
    if (M.ajouter()) {
        QMessageBox::information(this, "Ajout", "Machine ajoutée avec succès.");
        close();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de la machine.");
    }
}
