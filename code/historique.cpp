#include "historique.h"
#include "ui_historique.h"

historique::historique(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::historique)
{
    ui->setupUi(this);
}

historique::~historique()
{
    delete ui;
}

QSqlQueryModel *historique::afficherHistorique(QString query)
{

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    ui->listView_historique->setModel(model);
    return model;
}

void historique::on_pushButton_hist_clicked()
{
    QString query = "SELECT ACTIVITE FROM HISTORIQUE";
    QSqlQueryModel *model = afficherHistorique(query);
    ui->listView_historique->setModel(model);
}
