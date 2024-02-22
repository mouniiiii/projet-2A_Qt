#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMainWindow>

namespace Ui
{
    class authentification;
}

class authentification : public QMainWindow
{
    Q_OBJECT

public:
    explicit authentification(QWidget *parent = nullptr);
    ~authentification();

private slots:
    void on_loginButton_clicked();

    void on_cancelButton_clicked();
signals:
    void loggedIn(const QString& role);

private:
    Ui::authentification *ui;
};

#endif // AUTHENTIFICATION_H
