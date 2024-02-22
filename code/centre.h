#ifndef CENTRE_H
#define CENTRE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

#include <QAbstractItemModel>
using namespace std;


class Centre
{
private:
    int id_centre;
    QString nom_centre;
    QString adr;
    int capacite;

public:
    //getters
    int getid_centre(){return id_centre;}
    int getcap(){return capacite;}
    QString getnom_centre(){return nom_centre;}
    QString getadr(){return adr;}


    //setters
    void setid_centre(int id_centre) {this->id_centre=id_centre;}
    void setcap(int capacite) {this->capacite=capacite;}
    void setnom_centre(int nom_centre) {this->nom_centre=nom_centre;}
    void setadr(QString adr) {this->adr=adr;}





        //CRUD
        bool ajouter();
        bool supprimer(int);
        //bool modifier(int,QString,QString,int);
        bool modifier(int);
        QSqlQueryModel *afficher();
        //constructeurs
        Centre();
        Centre(int,QString,QString,int);

        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *tri(int);


};

#endif // CENTRE_H
