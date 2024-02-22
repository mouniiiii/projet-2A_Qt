#ifndef CALENDER_H
#define CALENDER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui
{
    class calender;
}

class calender : public QMainWindow
{
    Q_OBJECT

public:
    explicit calender(QWidget *parent = nullptr);
    ~calender();
    void on_calender_clicked();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::calender *ui;
};

#endif // CALENDER_H
