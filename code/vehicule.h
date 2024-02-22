#ifndef VEHICULE_H
#define VEHICULE_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QTextBrowser>


class Vehicule
{
    QString MATRICULE,TYPE_V,MARQUE,N_CHASSIS;
public:
    //constructeur
    Vehicule(){}
    Vehicule(QString,QString,QString,QString);
    //getteur
    QString getMatricule(){return MATRICULE;}
    QString getType_v(){return TYPE_V;}
    QString getMarque(){return MARQUE;}
    QString getN_chassis(){return N_CHASSIS;}
    //setteur
    void setMatricule(QString M){ MATRICULE=M;}
    void setType_v(QString V){TYPE_V=V;}
    void setMarque(QString MA){MARQUE= MA;}
    void setN_chassis(QString N){ N_CHASSIS=N;}

    bool ajouter_vehicule();
    QSqlQueryModel * afficher_vehicule();
    bool supprimer_vehicule(QString);
    bool modifier_vehicule();
    void charger(QString);
    QSqlQueryModel * research_vehicule(QString);
    QSqlQueryModel * rechercher_vehicule_matricule(QString);
    QSqlQueryModel * rechercher_vehicule_type(QString);
    QSqlQueryModel * rechercher_vehicule_num_chassis(QString);
    QSqlQueryModel * rechercher_vehicule_marque(QString);
    void exporterPdf(QTextBrowser *text);
    QSqlQueryModel *tri (int);

};

#endif // VEHICULE_H
