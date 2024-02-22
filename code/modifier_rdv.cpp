#include "modifier_rdv.h"
#include "ui_modifier_rdv.h"
#include "QMessageBox"
#include "rdv.h"
#include "QDebug"

// Modifier_RDV::Modifier_RDV(QWidget *parent) :
Modifier_RDV::Modifier_RDV(int g_ID_RDV, QWidget *parent) : QMainWindow(parent),
                                                            ui(new Ui::Modifier_RDV)
{
    ui->setupUi(this);
    RDV r;
    r.charger(g_ID_RDV);

    // recuperation des info
    ui->CENTRE->setCurrentText(r.getCentre());

    QString ID_RDV_String = QString::number(r.getID_RDV());
    ui->ID_RDV->setText(ID_RDV_String);

    // QDate date_string_on_db = r.getDate();
    // QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy HH24:mm");
    ui->DATE_RDV->setDateTime(r.getDate());

    // rafrechir
    this->repaint();
}

Modifier_RDV::~Modifier_RDV()
{
    delete ui;
}

void Modifier_RDV::on_pushButton_mod_clicked()
{

    // recuperation des info
    int ID_RDV = ui->ID_RDV->text().toInt();
    QDateTime DATE = ui->DATE_RDV->dateTime();
    QString CENTRE = ui->CENTRE->currentText();

    RDV r(ID_RDV, DATE, CENTRE);

    bool test = r.modifier(ID_RDV);
    // bool test=r.modifier(rowData.toInt());

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Modification effectuee.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Modification non effectuee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);

    this->hide(); // fermer la page
}
