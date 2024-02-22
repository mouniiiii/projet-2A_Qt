#ifndef STAT_RDV_H
#define STAT_RDV_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui
{
    class stat_rdv;
}

class stat_rdv : public QMainWindow
{
    Q_OBJECT

public:
    explicit stat_rdv(QWidget *parent = nullptr);
    ~stat_rdv();

    QChartView *chartView;

    // stat centre
    void on_stat_clicked();

private:
    Ui::stat_rdv *ui;
};

#endif // STAT_RDV_H
