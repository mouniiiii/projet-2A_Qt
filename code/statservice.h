#ifndef STATSERVICE_H
#define STATSERVICE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts>


#include <QDialog>

namespace Ui {
class statservice;
}

class statservice : public QDialog
{
    Q_OBJECT

public:
    explicit statservice(QWidget *parent = nullptr);
    ~statservice();
    void createChart();

  QChartView *chartView;
private slots:
    void on_pushButton_MainAjout_clicked();

private:
    Ui::statservice *ui;
};

#endif // STATSERVICE_H
