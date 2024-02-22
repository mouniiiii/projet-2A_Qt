#include "statistique.h"
#include "ui_statistique.h"
#include "ajouter.h"
#include "vehicule.h"
#include "mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QVBoxLayout>
statistique::statistique(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);

    Vehicule v;

    QtCharts::QBarSet *set = new QtCharts::QBarSet("Numero");
    *set << v.rechercher_vehicule_type("voiture")->rowCount() << v.rechercher_vehicule_type("moto")->rowCount() << v.rechercher_vehicule_type("camion")->rowCount();
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries(this);
    series->append(set);


    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->setTitle("Nombre Du Type");
    chart->createDefaultAxes();
    chart->addSeries(series);


    QStringList categories;
    categories << "voiture"<<"moto"<<"camion";

    QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
    axis->append(categories);
    chart->setAxisX(axis, series);


    QtCharts::QChartView * m_chartView = new QtCharts::QChartView(chart, this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(m_chartView);

    qDeleteAll(ui->widget->children());

    ui->widget->setLayout(layout);
}

statistique::~statistique()
{
    delete ui;
}

void statistique::on_pushButton_clicked()
{
    this->close();
}

void statistique::on_pushButton_supprimer_clicked()
{
    this->close();
    MainWindow * window = new MainWindow;
    window->show();
}

void statistique::on_pushButton_modifier_clicked()
{
    this->close();
    Ajouter * window = new Ajouter;
    window->show();
}
