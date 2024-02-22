#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QDebug>
#include<QTextBrowser>
#include <QFileDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFont>
class Service
{
public:

    Service();
    Service(int, QString, float);
    void setIdService(int id) { ID_SERVICE = id; };
    void setTPE(QString t) { TYPE = t; };
    void setPRIX(float p) { PRIX= p; };


    int get_idservice() { return ID_SERVICE; };
    QString get_type() { return TYPE; };
    float get_Prix() { return PRIX; };


    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher_remise(int);
    QSqlQueryModel *afficher_remise2(int);
    QSqlQueryModel *afficher_remise3(int);
    bool supprimer(int);
    bool modifier(int);
    void charger(int);
    void exporterpdf(QTextBrowser *text);
    QSqlQueryModel *recherche_Service(QString var);
    QSqlQueryModel *tri_service(int);



private:
    int ID_SERVICE;
    QString TYPE;
    int PRIX;

};

#endif // SERVICE_H
