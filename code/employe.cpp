#include "employe.h"
#include <QDebug>
#include <QDate>
#include <QString>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QTextBrowser>
#include <QFileDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFont>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

employe::employe(int a, QString b, QString c, QString d, QString e)
{
    CIN = a;
    NOM_EMP = b;
    PRENOM_EMP = c;
    ROLE = d;
    MDP = e;
}

bool employe::ajouter_employe()
{
    QSqlQuery query;
    QString res = QString::number(CIN);
    // prepare  method in database to prepare a sql statment to execute
    query.prepare("insert into GESTION_EMPLOYES(CIN,NOM_EMP,PRENOM_EMP,ROLE,MDP,DATE_AJOUT) values(:CIN,:NOM_EMP,:PRENOM_EMP,:ROLE,:MDP,SYSDATE)");
    // création des variables liées
    // bindValue méthode permet d'associer une valeur à un espace réservé, afin que l'instruction puisse être exécutée avec la valeur spécifiée.
    query.bindValue(":CIN", res);
    query.bindValue(":NOM_EMP", NOM_EMP);
    query.bindValue(":PRENOM_EMP", PRENOM_EMP);
    query.bindValue(":ROLE", ROLE);
    query.bindValue(":MDP", MDP);

    // Call ajouterHistorique after the query execution is successful
    ajouterHistorique("Ajout", "Employe", CIN);
    return query.exec(); // exec() envoie la requette pour l'executer
}
QSqlQueryModel *employe::afficher_employe()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select * from  GESTION_EMPLOYES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_EMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MDP"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_AJOUT"));

    return model;
}

bool employe::supprimer_employe(int CIN)
{

    QSqlQuery query;

    query.prepare("delete from GESTION_EMPLOYES where CIN =:CIN");
    query.bindValue(0, CIN);

    // return query.exec();
    bool success = query.exec();
    if (success)
    {
        ajouterHistorique("Suppression", "Employe", CIN);
    }

    return success;
}

bool employe::modifier_employe(int CIN)
{
    QSqlQuery query;
    QString res = QString::number(CIN);

    query.prepare("Update GESTION_EMPLOYES set CIN=:cin, NOM_EMP=:nom, PRENOM_EMP=:prenom, ROLE=:role, MDP=:mdp where CIN=:cin");
    query.bindValue(":cin", res);
    query.bindValue(":nom", NOM_EMP);
    query.bindValue(":prenom", PRENOM_EMP);
    query.bindValue(":role", ROLE);
    query.bindValue(":mdp", MDP);
    // query.bindValue(":date_ajout",DATE_AJOUT);

    return query.exec();
}

void employe::cahrger_employe(int CINE)
{

    QSqlQueryModel *model = new QSqlQueryModel();

    QString CIN_String = QString::number(CINE);

    model->setQuery("select * from GESTION_EMPLOYES where CIN=" + CIN_String + " ");

    // Récupérer les données de la ligne sélectionnée
    CIN = model->data(model->index(0, 0)).toInt();
    NOM_EMP = model->data(model->index(0, 1)).toString();
    PRENOM_EMP = model->data(model->index(0, 2)).toString();
    ROLE = model->data(model->index(0, 3)).toString();
    MDP = model->data(model->index(0, 4)).toString();
    DATE_AJOUT = model->data(model->index(0, 5)).toDate();
}

QSqlQueryModel *employe::recherche_employe(QString var)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM GESTION_EMPLOYES WHERE CIN LIKE '%" + var + "%' or ROLE LIKE '%" + var + "%' ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EMP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_RMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ROLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MDP"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_RENDEZ_VOUS"));

    return model;
}

QSqlQueryModel *employe::triCIN2()
{

    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT* FROM GESTION_EMPLOYES ORDER BY CIN ASC");

    return model;
}

QSqlQueryModel *employe::triCIN3()
{

    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT* FROM GESTION_EMPLOYES ORDER BY CIN DESC");

    return model;
}

void employe::exporterpdf(QTextBrowser *text)
{

    QSqlQuery qry;
    std::list<QString> tt;
    // Ajout du titre "employe" en bleu
    tt.push_back("<span style='color: #1687A7; font-size: 20px; font-weight: bold;'>EMPLOYE</span><br><br>");
    qry.exec("select * from GESTION_EMPLOYES");
    while (qry.next())
    {
        tt.push_back("<span style='font-size: 12px;'>CIN: " + qry.value(0).toString() + "<br>" + "NOM_EMP :" + qry.value(1).toString() + "<br>" + "PRENOM_EMP: " + qry.value(2).toString() + "<br>" + "ROLE: " + qry.value(3).toString() + "<br>" + "MDP: " + qry.value(4).toString() + "<br>" + "DATE_AJOUT: " + qry.value(5).toDate().toString(Qt::ISODate) + "<br></span>");
    }

    for (std::list<QString>::iterator it = tt.begin(); it != tt.end(); ++it) // nbr empl
    {
        // text->setText(text->toPlainText()+*it + "\n");
        text->setText(text->toHtml() + *it + "<br>");
    }

    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Export PDF", QString(), "*.pdf");
    // QFileDialog object to get the desired file name and path to save the PDF file
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    // Impression des données au format HTML
    QTextDocument doc;
    doc.setHtml(text->toHtml());

    // Draw the contents of the QTextDocument to the printer
    QPainter painter(&printer);
    doc.drawContents(&painter);

    // Ajout de l'image à droite de la page
    QPixmap img(":/images/icons/logo.png");
    int imgWidth = printer.pageRect().width() / 4;
    int imgHeight = imgWidth * img.height() / img.width();
    painter.drawPixmap(QRect(printer.pageRect().width() - imgWidth, 0, imgWidth, imgHeight), img);

    text->print(&printer);
    QMessageBox::information(nullptr, QObject::tr("Export PDF"),
                             QObject::tr("Export avec succes .\n"
                                         "Click OK to exit."),
                             QMessageBox::Ok);
}

void employe::ajouterHistorique(QString action, QString type, int id)
{
    QSqlQuery query1;
    query1.prepare("select * from HISTORIQUE where TRUNC(HISTORIQUE_DATES) = TRUNC(SYSDATE)");
    query1.exec();

    // QString date=QDateTime::currentDateTime().toString("dddd, dd MMMM yyyy");
    QString date1 = QDateTime::currentDateTime().toString("dd/MM/yy");
    QString time = QDateTime::currentDateTime().toString("hh:mm");
    QString activite = "\n    " + date1 + "   -   " + time + " \t    " + action + " " + type + " d'identifiant:  " + QString::number(id) + " \n";

    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE (activite, HISTORIQUE_DATES) VALUES (:activite, SYSDATE)");
    query.bindValue(":activite", activite);
    query.exec();

    //    activite = "\n\t\t\t\t" + date + "\n";
    if (!query1.next()) // if first activity of the day
    {
        // activite = "\n\t\t\t\t" + date + "\n";

        query.prepare("INSERT INTO HISTORIQUE (activite, HISTORIQUE_DATES) VALUES (:activite, SYSDATE)");
        query.bindValue(":activite", activite);
        query.exec();
    }
    else
    {
        query.prepare("delete from HISTORIQUE where TRUNC(HISTORIQUE_DATES) = TRUNC(SYSDATE) and activite = :activite ");
        query.bindValue(":activite", activite);
        query.exec();

        query.prepare("INSERT INTO HISTORIQUE (activite, HISTORIQUE_DATES) VALUES (:activite, SYSDATE)");
        query.bindValue(":activite", activite);
        query.exec();
    }
}
