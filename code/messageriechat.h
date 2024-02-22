#ifndef MESSAGERIECHAT_H
#define MESSAGERIECHAT_H
#include<QDebug>
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
#include <QDialog>

namespace Ui {
class Messageriechat;
}

class Messageriechat : public QDialog
{
    Q_OBJECT

public:
    explicit Messageriechat(QWidget *parent = nullptr);
    ~Messageriechat();
    void addmessage();

private:
    Ui::Messageriechat *ui;
};

#endif // MESSAGERIECHAT_H
