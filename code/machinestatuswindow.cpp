#include "machinestatuswindow.h"
#include "ui_machinestatuswindow.h"


MachineStatusWindow::MachineStatusWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MachineStatusWindow)
{
    ui->setupUi(this);
    //////////////////////////
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    //le slot update_label suite à la reception du signal readyRead (reception des données).
    /////////////////////////
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'Fonctionnel'");
    query.exec();
    query.next();

    int nb_fonctionnel = query.value(0).toInt();
    query.prepare("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'En panne'");
    query.exec();
    query.next();
    int nb_en_panne = query.value(0).toInt();

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    view->setBackgroundBrush(QBrush(QColor(240, 240, 240)));

    scene->setSceneRect(view->rect());

    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);

    setLayout(layout);

    qreal radius = 100 / 4;
    qreal spacing = radius / 4;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    keyLabel = new QLabel(this);
    keyLabel->setText("<font color='black' size='4'><b>Key:</b></font><br>"
                      "<font color='green'>Fonctionnel</font><br>"
                      "<font color='red'>En panne</font>");
    keyLabel->setAlignment(Qt::AlignCenter);

    QGroupBox* keyBox = new QGroupBox(this);
    keyBox->setObjectName("keyBox");
    QVBoxLayout* keyLayout = new QVBoxLayout(keyBox);
    keyLayout->addWidget(keyLabel);
    keyBox->setLayout(keyLayout);

    keyBox->setStyleSheet("QGroupBox#keyBox {"
                          "border-radius: 5px;"
                          "background-color: #f5f5f5;"
                          "border: 1px solid #ccc;"
                          "}");

    layout->addWidget(keyBox);
    ///////////
    QPushButton* button = new QPushButton(this);
    button->setText("Envoyer à Arduino!");
    connect(button, &QPushButton::clicked, this, &MachineStatusWindow::handleButtonClick);
    button->setStyleSheet("QPushButton {"
                          "background-color: #007acc;"
                          "border: none;"
                          "color: white;"
                          "padding: 8px 16px;"
                          "border-radius: 5px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #006bb3;"
                          "}");
    layout->addWidget(button);
    ///////////
    if (nb_fonctionnel > 0) {
        brush.setColor(QColor("#7CB342"));
        for (int i = 0; i < nb_fonctionnel; i++) {
            QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-radius/2, -radius/2, radius, radius);
            circle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            circle->setBrush(brush);
            circle->setPos(i*(radius+spacing) - (nb_fonctionnel-1)*(radius+spacing)/2, -radius/2);
            QString machineId;
            if (getMachineId(i, "Fonctionnel", machineId)) {
                circle->setToolTip("Machine ID: " + machineId);
            }
            scene->addItem(circle);
        }
    }

    if (nb_en_panne > 0) {
        brush.setColor(QColor("#E53935"));
        for (int i = 0; i < nb_en_panne; i++) {
            QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-radius/2, -radius/2, radius, radius);
            circle->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
            circle->setBrush(brush);
            circle->setPos(i*(radius+spacing) - (nb_en_panne-1)*(radius+spacing)/2, radius/2);
            QString machineId;
            if (getMachineId(i, "En panne", machineId)) {
                // Set the tooltip to show the machine's ID
                circle->setToolTip("Machine ID: " + machineId);
            }
            scene->addItem(circle);
            QTimer* timer = new QTimer(this);
            connect(timer, &QTimer::timeout, [=]() {
                if (circle->brush().color() == QColor("#E53935")) {
                    circle->setBrush(QBrush(Qt::transparent));
                } else {
                    circle->setBrush(QBrush(QColor("#E53935")));
                }
            });
            timer->start(500);
        }
    }

    setFixedSize(500, 400);
    view->setToolTipDuration(5000);
}

bool MachineStatusWindow::getMachineId(int index, const QString& state, QString& machineId) {
    bool success = false;

    QSqlQuery query;
    query.prepare("SELECT ID_MACHINE FROM GESTION_MACHINES WHERE ETAT = :state ORDER BY ID_MACHINE ASC");
    query.bindValue(":state", state);
    if (query.exec() && query.next()) {
        query.seek(index);
        machineId = query.value(0).toString();
        success = true;
    }

    return success;
}

void MachineStatusWindow::update_label()
{
    data=A.read_from_arduino();
    QSqlQuery query;
    qDebug() << data;
    QSqlQuery query1;
    query1.prepare("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'En panne'");
    query1.exec();
    query1.next();
    int nb_en_panne = query1.value(0).toInt();
    if((data=="1") && (nb_en_panne!=0))
    {
        query.prepare("insert into ALERTS (Alert) "
                      "values(:Alert)");
        query.bindValue(":Alert", "Panne");
        query.exec();
        QMessageBox::critical(nullptr, QObject::tr("Status"),
                              QObject::tr("Panne!!\n"
                                          "Taper sur Ok pour fermer."), QMessageBox::Ok);

    }else if (data=="0")
    {
        query.prepare("insert into ALERTS (Alert) "
                      "values(:Alert)");
        query.bindValue(":Alert", "Incendie");
        query.exec();
        QMessageBox::critical(nullptr, QObject::tr("Status"),

                              QObject::tr("Incendie!!\n"
                                          "Taper sur Ok pour fermer."), QMessageBox::Ok);
    }else
    {
        query.prepare("insert into ALERTS (Alert) "
                      "values(:Alert)");
        query.bindValue(":Alert", "Normal");
        query.exec();
        QMessageBox::information(nullptr, QObject::tr("Status"),
                                 QObject::tr("Bien (: !\n"
                                             "Taper sur Ok pour fermer."), QMessageBox::Ok);
    }
}

void MachineStatusWindow::handleButtonClick()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'Fonctionnel'");
    query.exec();
    query.next();
    QByteArray nb_fonctionnel = query.value(0).toByteArray();
    A.write_to_arduino(nb_fonctionnel);

    query.prepare("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'En panne'");
    query.exec();
    query.next();
    QByteArray nb_en_panne = query.value(0).toByteArray();
    A.write_to_arduino(nb_en_panne);
}


MachineStatusWindow::~MachineStatusWindow()
{
    A.close_arduino();
    delete ui;
}
