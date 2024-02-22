#include "machine.h"
#include "mainwindow.h"
Machine::Machine()
{  
}

Machine::Machine(int a, QString b, QString c, int d)
{
    ID_MACHINE = a;
    ETAT = b;
    DESCRIPTION = c;
    ID_SERVICE = d;

}

bool Machine::ajouter()
{
    QSqlQuery query;
    bool success = query.prepare("insert into GESTION_MACHINES (ID_MACHINE,ETAT,DESCRIPTION,ID_SERVICE) "
                                 "values(:ID_MACHINE,:ETAT,:DESCRIPTION,:ID_SERVICE)");
    if (!success) {
        qDebug() << "Failed to prepare query:" << query.lastError().text();
        return false;
    }

    query.bindValue(":ID_MACHINE", QString::number(ID_MACHINE));
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":ID_SERVICE", ID_SERVICE);

    success = query.exec();
    if (!success) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
    return success;
}

QSqlQueryModel *Machine::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select M.ID_MACHINE,M.ETAT,M.DESCRIPTION,TYPE from GESTION_MACHINES M join GESTION_SERVICES S ON M.ID_SERVICE=S.ID_SERVICE ORDER BY ID_MACHINE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID MACHINE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE SERVICE"));

    return model;
}
bool Machine::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("Delete from GESTION_MACHINES where ID_MACHINE= :ID_MACHINE");
    query.bindValue(":ID_MACHINE", res);
    return query.exec();
}

bool Machine::modifier(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("Update GESTION_MACHINES SET ETAT=:ETAT , DESCRIPTION=:DESCRIPTION,ID_SERVICE=:ID_SERVICE where ID_MACHINE= :ID_MACHINE");
    query.bindValue(":ID_MACHINE", res);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":DESCRIPTION", DESCRIPTION);
    query.bindValue(":ID_SERVICE", ID_SERVICE);
    MainWindow w;
    w.checkMachineStatus();
    return query.exec();
}

void Machine::charger(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString ID_MACHINE_String = QString::number(id);
    model->setQuery("select * from GESTION_MACHINES where ID_MACHINE=" + ID_MACHINE_String + " ");

    if (model->rowCount() > 0) {
        ID_MACHINE = model->data(model->index(0, 0)).toInt();
        ETAT = model->data(model->index(0, 1)).toString();
        DESCRIPTION = model->data(model->index(0, 2)).toString();
        ID_SERVICE = model->data(model->index(0, 3)).toInt();
    }

    delete model;
}


QSqlQueryModel *Machine::recherche_Machine(QString var)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT M.ID_MACHINE, M.ETAT, M.DESCRIPTION, S.TYPE "
                    "FROM GESTION_MACHINES M "
                    "JOIN GESTION_SERVICES S ON M.ID_SERVICE = S.ID_SERVICE "
                    "WHERE M.ID_MACHINE LIKE '%" + var + "%' OR M.ETAT LIKE '%" + var + "%' "
                    "ORDER BY M.ID_MACHINE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID MACHINE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE SERVICE"));

    return model;
}

QSqlQueryModel* Machine::tri_Machine(int a)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString queryStr = "SELECT M.ID_MACHINE, M.ETAT, M.DESCRIPTION, S.TYPE "
                       "FROM GESTION_MACHINES M "
                       "JOIN GESTION_SERVICES S ON M.ID_SERVICE = S.ID_SERVICE "
                       "ORDER BY M.ID_MACHINE";

    if (a == 0) {
        queryStr += " DESC";
    }

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":ID_MACHINE", ID_MACHINE);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID MACHINE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE SERVICE"));

    return model;
}


void Machine::exporterpdf(QTextBrowser *text)
{
    // Create header for the PDF
    QString header = "<div align='center'><img src=':/images/icons/logo.png'></div>"
                     "<h1 align='center'>Rapport Machines</h1>"
                     "<div align='right'>Date: " + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "</div>";

    // Create a HTML table to display the data
    QString table = "<table style='border-collapse: collapse; width: 100%; font-size: 14px; margin-top: 20px;'>"
                    "<thead>"
                    "<tr style='background-color: #1687A7; color: #fff; font-weight: bold;'>"
                    "<td style='padding: 10px; border: 1px solid #ddd;'>ID</td>"
                    "<td style='padding: 10px; border: 1px solid #ddd;'>Etat</td>"
                    "<td style='padding: 10px; border: 1px solid #ddd;'>Description</td>"
                    "<td style='padding: 10px; border: 1px solid #ddd;'>Type</td>"
                    "</tr>"
                    "</thead>"
                    "<tbody>";

    // Fetch data from the database and add it to the HTML table
    QSqlQuery qry("SELECT M.ID_MACHINE, M.ETAT, M.DESCRIPTION, TYPE FROM GESTION_MACHINES M JOIN GESTION_SERVICES S ON M.ID_SERVICE=S.ID_SERVICE");
    while (qry.next())
    {
        table += "<tr>"
                 "<td style='padding: 10px; border: 1px solid #ddd;'>" + qry.value(0).toString() + "</td>"
                                                                                                   "<td style='padding: 10px; border: 1px solid #ddd;'>" + qry.value(1).toString() + "</td>"
                                                                                                                                                                                     "<td style='padding: 10px; border: 1px solid #ddd;'>" + qry.value(2).toString() + "</td>"
                                                                                                                                                                                                                                                                       "<td style='padding: 10px; border: 1px solid #ddd;'>" + qry.value(3).toString() + "</td>"
                                                                                                                                                                                                                                                                                                                                                         "</tr>";
    }

    // Close the HTML table and add it to the document
    table += "</tbody></table>";
    QString html = "<html><head><meta content='text/html;charset=utf-8'></head><body>" + header + table + "</body></html>";

    // Create the PDF document
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(html);

    QPainter painter(&printer);
    doc.drawContents(&painter);

    text->print(&printer);

    // Show success message
    QMessageBox::information(nullptr, QObject::tr("Export PDF"),
                             QObject::tr("Export successful.\nClick OK to exit."), QMessageBox::Ok);
}
