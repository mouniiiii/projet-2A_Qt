#include "service.h"
#include<QDebug>
#include<QString>
Service::Service()
{
}

Service::Service(int a, QString b, float c)
{
    ID_SERVICE = a;
    TYPE = b;
    PRIX = c;

}

bool Service::ajouter()
{
    qDebug()<<ID_SERVICE;
    qDebug()<<TYPE;
    qDebug()<<PRIX;
    QSqlQuery query;
    query.prepare("insert into GESTION_SERVICES (ID_SERVICE,TYPE,PRIX) values(:ID_SERVICE,:TYPE,:PRIX);");
    query.bindValue(":ID_SERVICE", ID_SERVICE);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":PRIX", PRIX);


    return query.exec();
}

QSqlQueryModel *Service::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select ID_SERVICE, TYPE,PRIX from GESTION_SERVICES  ORDER BY ID_SERVICE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SERVICE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));


    return model;
}
QSqlQueryModel* Service::afficher_remise(int a)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT ID_SERVICE, TYPE, PRIX - (PRIX * 0.1) AS PRIX_REMISE FROM GESTION_SERVICES ORDER BY ID_SERVICE DESC";

    if (a) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SERVICE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX_REMISE"));
    } else {
        model->clear();
    }

    return model;
}


QSqlQueryModel *Service::afficher_remise2(int a)
{    
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "select ID_SERVICE, TYPE,PRIX-(PRIX*0.15) from GESTION_SERVICES  ORDER BY ID_SERVICE DESC";

    if (a) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SERVICE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX_REMISE"));
    } else {
        model->clear();
    }

    return model;
}

QSqlQueryModel *Service::afficher_remise3(int a)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "select ID_SERVICE, TYPE,PRIX-(PRIX*0.3) from GESTION_SERVICES  ORDER BY ID_SERVICE DESC";

    if (a) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SERVICE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX_REMISE"));
    } else {
        model->clear();
    }

    return model;
}

bool Service::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("Delete from GESTION_SERVICES where ID_SERVICE= :ID_SERVICE");
    query.bindValue(":ID_SERVICE", res);

    return query.exec();
}

bool Service::modifier(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("Update GESTION_SERVICES SET TYPE=:TYPE , PRIX=:PRIX where ID_SERVICE=:ID_SERVICE");
    query.bindValue(":ID_SERVICE", res);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":PRIX", PRIX);

    return query.exec();
}

void Service::charger(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString ID_SERVICE_String = QString::number(id);

    model->setQuery("select * from GESTION_SERVICES where ID_SERVICE=" + ID_SERVICE_String + " ");
    ID_SERVICE = model->data(model->index(0, 0)).toInt();
    TYPE = model->data(model->index(0, 1)).toString();
    PRIX = model->data(model->index(0, 2)).toFloat();

}

QSqlQueryModel *Service::recherche_Service(QString var)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select ID_SERVICE,TYPE,PRIX from GESTION_SERVICES WHERE ID_SERVICE LIKE '%" + var + "%' or TYPE LIKE '%" + var + "%'ORDER BY ID_SERVICE");


    model->query().bindValue(":ID_SERVICE", ID_SERVICE);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SERVICE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));


    return model;
}

QSqlQueryModel *Service::tri_service(int a)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(a)
    {
        model->setQuery("select ID_SERVICE,TYPE,PRIX from GESTION_SERVICES  ORDER BY PRIX");
    }
    else
        model->setQuery("select ID_SERVICE,TYPE,PRIX from GESTION_SERVICES ORDER BY PRIX DESC");
    return model;
}

void Service::exporterpdf(QTextBrowser *text)
{
    QSqlQuery qry;
    std::list<QString> tt;
    tt.push_back("<span style='color: #251605; font-size: 40px; font-weight: bold;'>Nos service</span><br><br>");
    qry.exec("select ID_SERVICE,TYPE,PRIX from GESTION_SERVICES");
    while(qry.next())
    {
        tt.push_back("<span style='font-size: 30px;'>ID: "+qry.value(0).toString()+"<br>"+"TYPE:"+qry.value(1).toString()+"<br>"+"PRIX: "+qry.value(2).toString()+"<br></span>");
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
