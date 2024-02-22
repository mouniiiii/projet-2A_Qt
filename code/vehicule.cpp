#include "vehicule.h"
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFont>
#include <QMessageBox>
#include <QFileDialog>

Vehicule::Vehicule(QString MATRICULE,QString TYPE_V,QString MARQUE,QString N_CHASSIS)
{
    this->MATRICULE =MATRICULE;
    this->TYPE_V=TYPE_V;
    this->MARQUE=MARQUE;
    this->N_CHASSIS=N_CHASSIS;

}


bool Vehicule::ajouter_vehicule()
{
    QSqlQuery query;
     query.prepare("insert into GESTION_VEHICULES(MATRICULE,TYPE_V,MARQUE,N_CHASSIS)" "Values(:MATRICULE,:TYPE_V,:MARQUE,:N_CHASSIS)");
     query.bindValue(":MATRICULE",MATRICULE);
    query.bindValue(":TYPE_V",TYPE_V);
            query.bindValue(":MARQUE",MARQUE);
            query.bindValue(":N_CHASSIS",N_CHASSIS);
            return query.exec();
}
QSqlQueryModel * Vehicule::afficher_vehicule()
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES");
    return model;

}
bool Vehicule::supprimer_vehicule(QString MATRICULE)
{
    QSqlQuery query;
     query.prepare("delete from GESTION_VEHICULES where MATRICULE = :MATRICULE");
     query.bindValue(":MATRICULE",MATRICULE);
     return query.exec();
}

bool Vehicule::modifier_vehicule(){
    QSqlQuery query;


    query.prepare("UPDATE GESTION_VEHICULES set TYPE_V=:TYPE_V , MARQUE=:MARQUE , N_CHASSIS=:N_CHASSIS  where MATRICULE=:MATRICULE");


    query.bindValue(":MATRICULE",MATRICULE);
    query.bindValue(":TYPE_V",TYPE_V);
    query.bindValue(":MARQUE",MARQUE);
    query.bindValue(":N_CHASSIS",N_CHASSIS);

    return query.exec();
}

QSqlQueryModel * Vehicule::research_vehicule(QString MATRICULE)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES where MATRICULE = '"+MATRICULE+"'");
    return model;
}

QSqlQueryModel * Vehicule::rechercher_vehicule_matricule(QString MATRICULE)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES where MATRICULE like '%"+MATRICULE+"%'");
    return model;

}

QSqlQueryModel * Vehicule::rechercher_vehicule_type(QString type)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES where TYPE_V like '%"+type+"%'");
    return model;

}
QSqlQueryModel * Vehicule::rechercher_vehicule_num_chassis(QString num_chassis)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES where N_CHASSIS like '%"+num_chassis+"%'");
    return model;

}
QSqlQueryModel * Vehicule::rechercher_vehicule_marque(QString marque)
{
    QSqlQueryModel * model = new QSqlQueryModel;

    model->setQuery("select * from GESTION_VEHICULES where MARQUE like '%"+marque+"%'");
    return model;

}
void Vehicule::exporterPdf(QTextBrowser *text)
{
    QSqlQuery qry;
       std::list<QString> tt;
       tt.push_back("<span style='color: #251605; font-size: 40px; font-weight: bold;'>Vehicules</span><br><br>");
       qry.exec("select * from GESTION_VEHICULES");
       while(qry.next())
       {
           tt.push_back("<span style='font-size: 30px;'>MATRICULE: "+qry.value(0).toString()+"<br>"+"TYPE:"+qry.value(1).toString()+"<br>"+"MARQUE: "+qry.value(2).toString()+"<br><br>"+"NUM_chassis:"+qry.value(3).toString()+"<br></span>");
       }

       for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
       {
           text->setText(text->toHtml()+*it + "<br>");
       }

       QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
       //QFileDialog object to get the desired file name and path to save the PDF file
       if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);

       printer.setOutputFileName(fileName);

       // Impression des données au format HTML
       QTextDocument doc;
       doc.setHtml(text->toHtml());

       // Draw the contents of the QTextDocument to the printer
       QPainter painter(&printer);
       doc.drawContents(&painter);
       text->print(&printer);
       QMessageBox::information(nullptr, QObject::tr("Export PDF"),
                                QObject::tr("Export avec succes .\n"
                                            "Click OK to exit."), QMessageBox::Ok);

}
QSqlQueryModel *Vehicule::tri(int a)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(a)
    {
        model->setQuery("select * from GESTION_VEHICULES ORDER BY TYPE_V");
    }
    else
        model->setQuery("select * from GESTION_VEHICULES ORDER BY TYPE_V DESC");
    return model;
}
