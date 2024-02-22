#include "messageriechat.h"
#include "ui_messageriechat.h"
#include "qsqltablemodel.h"

Messageriechat::Messageriechat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Messageriechat)
{
    ui->setupUi(this);
}

Messageriechat::~Messageriechat()
{
    delete ui;
}

void Messageriechat::addmessage()
{

    QString message = ui->->text();

       QSqlQuery query;
       query.prepare("INSERT INTO chatmessage (sender, message) VALUES (:sender, :message)");
       query.bindValue(":sender", "Me");
       query.bindValue(":message", message);
       if (!query.exec()) {
           qDebug() << "Failed to insert message into database";
       }

       QSqlTableModel* model = new QSqlTableModel(this, db);
       model->setTable("chatmessage");
       model->select();
       ui->messageTable->setModel(model);
       ui->messageTable->setColumnHidden(0, true);
       ui->messageTable->setColumnWidth(1, 100);
       ui->messageTable->setColumnWidth(2, 200);

       ui->messageEdit->clear();
}
