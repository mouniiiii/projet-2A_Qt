#include "statmachine.h"
#include "ui_statmachine.h"
#include "drilldownslice.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>

QT_CHARTS_USE_NAMESPACE

StatMachine::StatMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatMachine)
{
    ui->setupUi(this);

    QChart *chart = new QChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *etatSeries = new QPieSeries();
    etatSeries->setName("Stat par etat - All");
    QSqlQuery q1,q2,q3;
    qreal tot=0,c1=0,c2=0;

    q1.prepare("SELECT * FROM GESTION_MACHINES");
    q1.exec();

    q2.prepare("SELECT * FROM GESTION_MACHINES WHERE ETAT='Fonctionnel'");
    q2.exec();

    q3.prepare("SELECT * FROM GESTION_MACHINES WHERE ETAT='En panne'");
    q3.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}

    c1=c1/tot;
    c2=c2/tot;
    QPieSeries *series = new QPieSeries();

    *series << new DrilldownSlice(c1, "Fonctionnel ", etatSeries);
    *series << new DrilldownSlice(c2, "En panne ", etatSeries);

    chart->addSeries(series);
    chart->legend()->show();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
    resize(700, 500);
}

StatMachine::~StatMachine()
{
    delete ui;
}


