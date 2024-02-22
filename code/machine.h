#ifndef MACHINE_H
#define MACHINE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextBrowser>
#include <QFileDialog>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPainter>
#include <QFont>
#include <QDate>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QApplication>
#include <QIcon>
#include <QtCore/QObject>

class Machine
{
public:
    Machine();
    Machine(int, QString, QString, int);
    void setIdMachine(int M) { ID_MACHINE = M; };
    void setEtat(QString E) { ETAT = E; };
    void setDescription(QString D) { DESCRIPTION = D; };
    void setIdService(int S) { ID_SERVICE = S; };
    int get_IdMachine() { return ID_MACHINE; };
    QString get_Etat() { return ETAT; };
    QString get_Description() { return DESCRIPTION; };
    int get_IdService() { return ID_SERVICE; };
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    void charger(int);
    QSqlQueryModel *recherche_Machine(QString var);
    QSqlQueryModel *tri_Machine(int);
    void exporterpdf(QTextBrowser *text);
    ~Machine(){};
private:
    int ID_MACHINE;
    QString ETAT;
    QString DESCRIPTION;
    int ID_SERVICE;
};

#endif // MACHINE_H
