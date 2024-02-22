#ifndef RDV_H
#define RDV_H

#include<QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include <QDateTime>

#include <QTableView>
#include <QSortFilterProxyModel>
#include <QtWidgets>

#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintDialog>

#include "rdv_arduino.h"

class RDV
{
private:
    int ID_RDV;
    QString CENTRE , MATRICULE;
    QDateTime DATE_RDV;


public:
    RDV();
    RDV(int , QDateTime , QString);
    ~RDV(){};

    int getID_RDV(){return ID_RDV;};
    QDateTime getDate(){return DATE_RDV;};
    QString getCentre(){return CENTRE;};
    QString getMatricule(){return MATRICULE;};

    void setID_RDV(int n){ID_RDV=n;};
    void setDate(QDateTime n){DATE_RDV=n;};
    void setCentre(QString n){CENTRE=n;};
    void setMatricule(QString n){MATRICULE=n;};


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    void charger(int);

    //Metier

    //void Rdv_auto(int id , const QDateTime& dateTime, const QString& centre);
    void Rdv_auto(int id , const QDateTime& dateTime, QTime heureDebut , QTime heureFin , const QString& centre);

    int Affecter_Matricule(int id);
    bool test_validite_rdv(QString Mat , QDateTime date);

    QSqlQueryModel * afficher_RDV_reserve();
    QSqlQueryModel * afficher_RDV_non_reserve();




    //*****trie
    void trie_tab_date(QTableView* tab , int colonne);
    //*****PDF
    void export_pdf(QString recherche , QTextBrowser *text);



};

#endif // RDV_H
