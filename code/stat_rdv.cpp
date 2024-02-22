#include "stat_rdv.h"
#include "ui_stat_rdv.h"

stat_rdv::stat_rdv(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::stat_rdv)
{
    ui->setupUi(this);
}

stat_rdv::~stat_rdv()
{
    delete ui;
}

// pie chart
void stat_rdv::on_stat_clicked()
{
    QSqlQuery q1, q2, q3; // requette
    qreal tot = 0, c1 = 0, c2 = 0;

    q1.prepare("SELECT * FROM GESTION_RDVS");
    q1.exec(); // La requête récupère toutes les lignes de la table,

    q2.prepare("SELECT * FROM GESTION_RDVS WHERE CENTRE='Ariena'");
    q2.exec();

    q3.prepare("SELECT * FROM GESTION_RDVS WHERE CENTRE='Tunis'");
    q3.exec();

    // les deux autres requêtes récupèrent uniquement les lignes où le champ "ROLE" est égal à "Tunis" et "Ariena",

    while (q1.next())
    {
        tot++;
    } // compter nbr totale rdv
    while (q2.next())
    {
        c1++;
    } // compter nbr Ariena
    while (q3.next())
    {
        c2++;
    } // compter nbr Tunis
    // la fonction utilise une boucle while pour compter le nombre total rdv et le nombre rdv dans chaque catégorie de centre.

    c1 = c1 / tot;
    c2 = c2 / tot; // calculer les pourcentages

    // Définir les tranches et le pourcentage de l'ensemble qu'elles occupent
    QPieSeries *series = new QPieSeries(); // QPieSeries pour stocker les données du graphique circulaire
    series->append("Ariena", c1);
    series->append("Tunis", c2);
    // La fonction utilise ensuite les classes QPieSeries et QChart de Qt pour créer le graphique circulaire.

    // Create the chart(graphique) widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();

    // Used to display the chart
    chartView = new QChartView(chart, ui->graphicsView);
    chartView->setRenderHint(QPainter::Antialiasing); // améliorer la qualité de l'affichage.
    chartView->setMinimumSize(700, 500);

    chartView->show();
}
