#include "rdv.h"
#include "QDebug"
#include <QSqlError>
#include <QMap>
#include <QList>
#include <QtNetwork>
#include <QFont>

RDV::RDV()
{
    ID_RDV = 0;
    // DATE_RDV=0;
    CENTRE = "";
}

RDV::RDV(int a, QDateTime b, QString d)
{
    ID_RDV = a;
    DATE_RDV = b;
    CENTRE = d;
}

bool RDV::ajouter()
{
    QSqlQuery query;
    QString ID_RDV_String = QString::number(ID_RDV);

    // prepare() prend la requete en parametre pour la recuperer a l'execution

    query.prepare("insert into GESTION_RDVS (ID_RDV, DATE_RDV , CENTRE )"
                  "values (:ID_RDV ,:DATE_RDV , :CENTRE)");

    // creation var
    query.bindValue(":ID_RDV", ID_RDV_String);
    query.bindValue(":DATE_RDV", DATE_RDV);
    query.bindValue(":CENTRE", CENTRE);
    /*qDebug() << CENTRE ;
    qDebug() << DATE_RDV ;*/

    return query.exec(); // exec envoie true ou false
}

void RDV::Rdv_auto(int id, const QDateTime &dateTime, QTime heureDebut, QTime heureFin, const QString &centre)
{
    // QTime heureDebut(9, 0); // heure de début des rendez-vous
    // QTime heureFin(12, 0); // heure de fin des rendez-vous
    QTime heureRdv = heureDebut;                               // dateTime.time(); // heure du rendez-vous
    QDate dateDuJour = dateTime.date();                        // date du rendez-vous
    QTime heureLimite(heureFin.hour() - 1, heureFin.minute()); // heure limite pour prendre un rendez-vous

    ID_RDV = id;
    CENTRE = centre;
    while (heureRdv <= heureLimite)
    {
        QDateTime dateRdv(dateDuJour, heureRdv); // date et heure du rendez-vous
        DATE_RDV = dateRdv;
        qDebug() << "id" << ID_RDV << "Rendez-vous le" << dateRdv.toString(Qt::ISODate) << "au centre" << centre;
        heureRdv = heureRdv.addSecs(1800); // ajouter une heure pour le prochain rendez-vous

        ajouter();
        ID_RDV++;
    }
}

QSqlQueryModel *RDV::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select * from GESTION_RDVS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CENTRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

    return model;
}

QSqlQueryModel *RDV::afficher_RDV_reserve()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select * from GESTION_RDVS where MATRICULE is not null ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CENTRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

    return model;
}

QSqlQueryModel *RDV::afficher_RDV_non_reserve()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select * from GESTION_RDVS where MATRICULE is null ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_RDV"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CENTRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MATRICULE"));

    return model;
}

bool RDV::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("Delete from GESTION_RDVS where ID_RDV= :ID_RDV");
    query.bindValue(":ID_RDV", res);

    return query.exec();
}

bool RDV::modifier(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("Update GESTION_RDVS SET DATE_RDV=:DATE_RDV , CENTRE='" + CENTRE + "' where ID_RDV= :ID_RDV");
    query.bindValue(":ID_RDV", res);
    query.bindValue(":DATE_RDV", DATE_RDV);

    return query.exec();
}

int RDV::Affecter_Matricule(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    if (test_validite_rdv(MATRICULE, DATE_RDV))
    {
        query.prepare("Update GESTION_RDVS SET MATRICULE='" + MATRICULE + "' where ID_RDV= :ID_RDV");
        query.bindValue(":ID_RDV", res);
        return query.exec();
    }
    else
    {
        return -1;
    }
}

bool RDV::test_validite_rdv(QString Mat, QDateTime date)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select count(*) from GESTION_RDVS where MATRICULE='" + Mat + "' ");

    int nb_count;
    nb_count = model->data(model->index(0, 0)).toInt();
    if (nb_count == 0)
    {
        return true;
    }

    model->setQuery("select max(DATE_RDV) as max_date from GESTION_RDVS where MATRICULE='" + Mat + "' ");

    QDateTime tmp_date;
    tmp_date = model->data(model->index(0, 0)).toDateTime();

    qDebug() << "tmp date : " << tmp_date.toString() << "date : " << date.toString();
    qDebug() << "diff : " << tmp_date.daysTo(date);

    if (tmp_date.daysTo(date) > 365)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RDV::charger(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString ID_RDV_String = QString::number(id);

    model->setQuery("select * from GESTION_RDVS where ID_RDV=" + ID_RDV_String + " ");

    // Récupérer les données de la ligne sélectionnée
    ID_RDV = model->data(model->index(0, 0)).toInt();
    DATE_RDV = model->data(model->index(0, 1)).toDateTime();
    // qDebug() << DATE_RDV;
    CENTRE = model->data(model->index(0, 2)).toString();
}

// Metier

//*****trie

void RDV::trie_tab_date(QTableView *tab, int colonne)
{
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(tab);
    proxyModel->setSourceModel(tab->model());
    proxyModel->setSortRole(Qt::EditRole);          // le rôle Qt::EditRole sera utilisé pour trier les données dans QSortFilterProxyModel.
    proxyModel->sort(colonne, Qt::DescendingOrder); // trie selon la colonne et l'ordre spécifié
    tab->setModel(proxyModel);                      // affecte le ProxyModel trié au tableView

    // tab->sortByColumn(colonne, Qt::DescendingOrder);
}

// pdf
void RDV::export_pdf(QString recherche, QTextBrowser *text)
{
    QSqlQuery qry;
    std::list<QString> tt;

    //*****
    // Ajout du titre
    tt.push_back("<span style='color: #1687A7; font-size: 15px; font-weight: bold;'>RDV</span><br><br>");
    //*****

    if (recherche == "")
    {
        qry.exec("select * from GESTION_RDVS");
    }

    else
    {
        qry.exec("select * from GESTION_RDVS where CENTRE like '%" + recherche + "%' ");
    }
    while (qry.next())
    {
        tt.push_back("ID_RDV: " + qry.value(0).toString() + "<br>" + "DATE: " + qry.value(1).toString() + "<br>" + "CENTRE: " + qry.value(2).toString() + "<br>" + "MATRICULE: " + qry.value(3).toString() + "<br>");
    }

    text->setText("");
    for (std::list<QString>::iterator it = tt.begin(); it != tt.end(); ++it)
    {
        // text->setText(text->toPlainText()+*it + "\n");
        text->setText(text->toHtml() + *it + "<br>");
    }

    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    //****
    // Impression des données au format HTML
    QTextDocument doc;
    doc.setHtml(text->toHtml());
    doc.print(&printer);

    // Draw the contents of the QTextDocument to the printer
    QPainter painter(&printer);
    doc.drawContents(&painter);

    // Ajout de l'image à droite de la page
    QPixmap img(":/images/icons/logo.png");
    int imgWidth = printer.pageRect().width() / 4;
    int imgHeight = imgWidth * img.height() / img.width();
    painter.drawPixmap(QRect(printer.pageRect().width() - imgWidth, 0, imgWidth, imgHeight), img);
    //****

    text->print(&printer);
    QMessageBox::information(nullptr, QObject::tr("Export PDF"),
                             QObject::tr("Export avec succes .\n"
                                         "Click OK to exit."),
                             QMessageBox::Ok);
}
