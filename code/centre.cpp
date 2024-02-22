#include "centre.h"
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QString>
#include "ui_mainwindow.h"

//Constructeur
Centre::Centre(){};


//Constructeur
Centre::Centre(int id_centre,QString nom_centre,QString adr,int capacite)
{
    this->id_centre=id_centre;
    this->capacite=capacite;
    this->nom_centre=nom_centre;
    this->adr=adr;
};


//CRUD
//Ajouter
bool Centre::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into GESTION_CENTRES (id_centre,nom_centre,adr,capacite) values(:id_centre, :nom_centre, :adr, :capacite)");
    query.bindValue(":id_centre", id_centre);
    query.bindValue(":nom_centre", nom_centre);
    query.bindValue(":adr", adr);
    query.bindValue(":capacite", capacite);

    return query.exec();
}


//Supprimer
bool Centre::supprimer(int id_centre)
{
    QSqlQuery query;
    query.prepare("delete from GESTION_CENTRES where id_centre=:id_centre");// kifma base de donnée
    query.bindValue(":id_centre", id_centre);

    return query.exec();
}

bool Centre::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("update GESTION_CENTRES set id_centre=:Id_centre,nom_centre=:Nom_centre,adr=:Adr,capacite=:Capacite where id_centre=:Id_centre");
    query.bindValue(":Id_centre",id_centre);
    query.bindValue(":Nom_centre",nom_centre);
    query.bindValue(":Adr",adr);
    query.bindValue(":Capacite",capacite);

    return query.exec();
}

QSqlQueryModel * Centre:: afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM GESTION_CENTRES ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

    return model;
};


QSqlQueryModel *Centre::rechercher(QString var)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from GESTION_CENTRES WHERE ID_centre LIKE '%" + var + "%' ORDER BY ID_CENTRE");

    model->query().bindValue(":id_centre", id_centre);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacite"));

    return model;
}

QSqlQueryModel *Centre::tri(int a)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(a)
        model->setQuery("select * from GESTION_CENTRES ORDER BY CAPACITE DESC");
    else
        model->setQuery("SELECT* FROM GESTION_CENTRES ");
    return model;
}
