#ifndef MESSAGERIE_H
#define MESSAGERIE_H

#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtGui/QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

namespace Ui {
class messagerie;
}

class messagerie : public QDialog
{
    Q_OBJECT

public:
    explicit messagerie(QWidget *parent = nullptr);
    ~messagerie();

private slots:
    void on_sendButton_clicked();
        void loadMessages();
        void on_pushButton_Mainenvoyer_clicked();

private:
            Ui::messagerie *ui;
            QStandardItemModel *messageModel;
            QSqlDatabase database;

};

#endif // MESSAGERIE_H
