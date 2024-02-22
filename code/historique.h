#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QDebug>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include "employe.h"
#include <QMainWindow>

namespace Ui
{
    class historique;
}

class historique : public QMainWindow
{
    Q_OBJECT

public:
    explicit historique(QWidget *parent = nullptr);
    ~historique();

    QSqlQueryModel *afficherHistorique(QString query);
    void on_pushButton_hist_clicked();

private:
    Ui::historique *ui;
};

#endif // HISTORIQUE_H
