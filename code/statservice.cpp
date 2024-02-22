#include "statservice.h"
#include "ui_statservice.h"

statservice::statservice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statservice)
{
    ui->setupUi(this);
    QSqlQuery q1,q2,q3; //requette
    qreal tot=0,c1=0,c2=0;

    q1.prepare("SELECT * FROM GESTION_SERVICES");
    q1.exec(); //La requête récupère toutes les lignes de la table,

        q2.prepare("SELECT * FROM GESTION_SERVICES WHERE PRIX>40");
    q2.exec();

    q3.prepare("SELECT * FROM GESTION_SERVICES WHERE PRIX<40");
    q3.exec();



        while (q1.next()){tot++;}//compter nbr totale service
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}


    c1=c1/tot;
    c2=c2/tot; //calculer les pourcentages


    QPieSeries *series = new QPieSeries();//QPieSeries pour stocker les données du graphique circulaire
    series->append("+40 ",c1);
    series->append("-40",c2);

    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->graphicsView);
    chartView->setRenderHint(QPainter::Antialiasing);//améliorer la qualité de l'affichage.
    chartView->setMinimumSize(700,500);

    chartView->show();
}

statservice::~statservice()
{
    delete ui;
}

void statservice::on_pushButton_MainAjout_clicked()
{
    QSqlQuery q1,q2,q3; //requette
    qreal tot=0,c1=0,c2=0;

    q1.prepare("SELECT * FROM GESTION_SERVICES");
    q1.exec(); //La requête récupère toutes les lignes de la table,

        q2.prepare("SELECT * FROM GESTION_SERVICES WHERE PRIX>40");
    q2.exec();

    q3.prepare("SELECT * FROM GESTION_SERVICES WHERE PRIX<40");
    q3.exec();



        while (q1.next()){tot++;}//compter nbr totale service
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}


    c1=c1/tot;
    c2=c2/tot; //calculer les pourcentages


    QPieSeries *series = new QPieSeries();//QPieSeries pour stocker les données du graphique circulaire
    series->append("+40 ",c1);
    series->append("-40",c2);

    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->graphicsView);
    chartView->setRenderHint(QPainter::Antialiasing);//améliorer la qualité de l'affichage.
    chartView->setMinimumSize(700,500);

    chartView->show();

}

