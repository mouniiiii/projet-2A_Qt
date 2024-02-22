#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QString>
#include <QTextBrowser>
#include <QTextBrowser>

#include <QDate>

class employe
{
private:
    int CIN;
    QString NOM_EMP, PRENOM_EMP, ROLE, MDP;
    QDate DATE_AJOUT;

public:
    // constructeur
    employe(){};
    employe(int, QString, QString, QString, QString, QDate);
    employe(int, QString, QString, QString, QString);

    // getters
    int getCIN() { return CIN; };
    QString getNOM_EMP() { return NOM_EMP; };
    QString getPRENOM_EMP() { return PRENOM_EMP; };
    QString getROLE() { return ROLE; };
    QString getMDP() { return MDP; };
    QDate getdate_ajout() { return DATE_AJOUT; };
    // setter
    void setCIN(int c) { CIN = c; };
    void setNOM_EMP(QString n) { NOM_EMP = n; };
    void setPRENOM_EMP(QString p) { PRENOM_EMP = p; };
    void setROLE(QString r) { ROLE = r; };
    void setMDP(QString m) { MDP = m; };
    void setdate_ajout(QDate d) { DATE_AJOUT = d; }

    // fonction
    bool ajouter_employe();
    QSqlQueryModel *afficher_employe();
    bool supprimer_employe(int);
    bool modifier_employe(int);
    void cahrger_employe(int);
    // les metiers
    QSqlQueryModel *recherche_employe(QString var);
    QSqlQueryModel *triCIN2();
    QSqlQueryModel *triCIN3();
    void exporterpdf(QTextBrowser *text);

    // nouvelles fonctions

    void ajouterHistorique(QString action, QString type, int id);
};

#endif // EMPLOYE_H
