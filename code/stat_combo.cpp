#include "stat_combo.h"
#include "ui_stat_combo.h"

stat_combo::stat_combo(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::stat_combo)
{
    ui->setupUi(this);
}

stat_combo::~stat_combo()
{
    delete ui;
}

// pie chart
void stat_combo::on_stat_clicked()
{
    QSqlQuery q1, q2, q3, q4, q5; // requette
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;

    q1.prepare("SELECT * FROM GESTION_EMPLOYES");
    q1.exec(); // La requête récupère toutes les lignes de la table,

    q2.prepare("SELECT * FROM GESTION_EMPLOYES WHERE ROLE='Employes'");
    q2.exec();

    q3.prepare("SELECT * FROM GESTION_EMPLOYES WHERE ROLE='Secretere'");
    q3.exec();

    q4.prepare("SELECT * FROM GESTION_EMPLOYES WHERE ROLE='Mecanicien'");
    q4.exec();

    q5.prepare("SELECT * FROM GESTION_EMPLOYES WHERE ROLE='Technicien'");
    q5.exec();

    // Les requêtes récupèrent uniquement les lignes où le champ "ROLE" est égal à chaque rôle.

    while (q1.next())
    {
        tot++;
    } // compter nbr totale employe

    while (q2.next())
    {
        c1++;
    } // compter nbr Employes

    while (q3.next())
    {
        c2++;
    } // compter nbr Secretes

    while (q4.next())
    {
        c3++;
    } // compter nbr Mecaniciens

    while (q5.next())
    {
        c4++;
    } // compter nbr Services

    c1 = c1 / tot;
    c2 = c2 / tot;
    c3 = c3 / tot;
    c4 = c4 / tot;

    // Définir les tranches et le pourcentage de l'ensemble qu'elles occupent
    QPieSeries *series = new QPieSeries(); // QPieSeries pour stocker les données du graphique circulaire
    series->append("Employes", c1);
    series->append("Secreteres", c2);
    series->append("Mecaniciens", c3);
    series->append("Techniciens", c4);

    // La fonction utilise ensuite les classes QPieSeries et QChart de Qt pour créer le graphique circulaire.

    // Create the chart(graphique) widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();

    // Used to show the chart
    chartView = new QChartView(chart, ui->graphicsView);
    chartView->setRenderHint(QPainter::Antialiasing); // améliorer la qualité de l'affichage.
    chartView->setMinimumSize(700, 500);

    chartView->show();
}
