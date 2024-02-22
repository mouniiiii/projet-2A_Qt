#include "mainwindow.h"
#include "ui_mainwindow.h"
//****NOUR
#include "employe.h"
#include "stat_combo.h"
#include "calender.h"
#include "authentification.h"
#include "historique.h"

//****Rania
#include "rdv.h"
#include "modifier_rdv.h"
#include "QMessageBox"
#include "stat_rdv.h"
#include "smtp.h"
#include <QtNetwork>

//****GHAITH

//****MAHMOUD

//****MOUNIR
#include "centre.h"

//****ZIED
#include <QSqlRecord>
#include <QDir>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>


///////////
#include <QPropertyAnimation>
#include <QEasingCurve>

bool MainWindow::isAuthenticated = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //////////////////////////
    if (!isAuthenticated)
    {
        authenticate();
        isAuthenticated = true;
        loadingScreen(4000);
    }

    //////////////////////////

    QLinearGradient gradient(0, 0, 0, 1);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setColorAt(0, QColor("#4B79A1"));
    gradient.setColorAt(1, QColor("#283E51"));
    ui->centralwidget->setAutoFillBackground(true);
    QPalette pal = ui->centralwidget->palette();
    pal.setBrush(QPalette::Background, gradient);
    ui->centralwidget->setPalette(pal);
    QString styleSheetMW =
            "QMainWindow {"
            "background-color: transparent;"
            "border: none;"
            "}"
            "QStatusBar {"
            "background-color: #222222;"
            "color: white;"
            "}";
    setStyleSheet(styleSheetMW);
    setWindowFlags(Qt::CustomizeWindowHint);




    QFont font("Arial", 12);
    ////MOUNIR
    QTabBar* tabBarM = ui->tabWidget->tabBar();
    tabBarM->setFont(font);

    tabBarM->setStyleSheet(
                "QTabBar::tab {"
                "background-color: #EDEDED;"
                "border: 2px solid #A3A3A3;"
                "border-bottom-color: #F0F0F0;"
                "min-width: 8ex;"
                "padding: 5px;"
                "font-size: 12px;"
                "color: #333;"
                "}"
                "QTabBar::tab:selected {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4A90E2, stop:1 #0077C2);"
                "border-bottom-color: #0077C2;"
                "color: white;"
                "}"
                "QTabBar::tab:hover {"
                "background-color: #4DA1FF;"
                "color: white;"
                "}"
                );

    ui->tabWidget->setStyleSheet(
                "QTabWidget::pane {"
                "border-top: 2px solid #A3A3A3;"
                "background-color: white;"
                "border-bottom-left-radius: 10px;"
                "border-bottom-right-radius: 10px;"
                "margin-top: -2px;"
                "}"
                );
    //////GESTIONS
    QTabBar* tabBar = ui->tabWidget_Gestions->tabBar();
    ////////////
    tabBar->setTabIcon(0, QIcon(":/images/icons/tab1.png"));
    tabBar->setTabIcon(1, QIcon(":/images/icons/tab2.png"));
    tabBar->setTabIcon(2, QIcon(":/images/icons/tab3.png"));
    tabBar->setTabIcon(3, QIcon(":/images/icons/tab4.png"));
    tabBar->setTabIcon(4, QIcon(":/images/icons/tab5.png"));
    tabBar->setTabIcon(5, QIcon(":/images/icons/tab6.png"));
    /////////////
    tabBar->setFont(font);

    tabBar->setStyleSheet(
                "QTabBar::tab {"
                "background-color: #EDEDED;"
                "border: 2px solid #A3A3A3;"
                "border-bottom-color: #F0F0F0;"
                "min-width: 8ex;"
                "padding: 5px;"
                "font-size: 12px;"
                "color: #333;"
                "}"
                "QTabBar::tab:selected {"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4A90E2, stop:1 #0077C2);"
                "border-bottom-color: #0077C2;"
                "color: white;"
                "}"
                "QTabBar::tab:hover {"
                "background-color: #4DA1FF;"
                "color: white;"
                "}"
                );

    ui->tabWidget_Gestions->setStyleSheet(
                "QTabWidget::pane {"
                "border-top: 2px solid #A3A3A3;"
                "background-color: white;"
                "border-bottom-left-radius: 10px;"
                "border-bottom-right-radius: 10px;"
                "margin-top: -2px;"
                "}"
                );

    //****NOUR
    ui->lineEdit_recherche->setPlaceholderText("Recherche...");
    QString styleSheetN = "QLineEdit#lineEdit_recherche {"
                          "  border: 2px solid gray;"
                          "  border-radius: 10px;"
                          "  padding: 5px;"
                          "  font-size: 16px;"
                          "  background-color: #f5f5f5;"
                          "}"
                          "QLineEdit#lineEdit_recherche:focus {"
                          "  border: 2px solid blue;"
                          "}";
    ui->lineEdit_recherche->setStyleSheet(styleSheetN);
    ui->tableView->setModel(emp.afficher_employe());
    //// EL ZINA DES TABLEUX
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                                 QTableView::item:selected { color: white; } \
                                 QHeaderView::section { background-color: #769aa8; color: white; }");
                                 ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(150);

    //******rania
    ui->lineEdit_recherche_2->setPlaceholderText("Recherche...");

    QString styleSheetR = "QLineEdit#lineEdit_recherche_2 {"
                          "  border: 2px solid gray;"
                          "  border-radius: 10px;"
                          "  padding: 5px;"
                          "  font-size: 16px;"
                          "  background-color: #f5f5f5;"
                          "}"
                          "QLineEdit#lineEdit_recherche_2:focus {"
                          "  border: 2px solid blue;"
                          "}";
    ui->lineEdit_recherche_2->setStyleSheet(styleSheetR);
    ui->tab_3->setModel(r_tmp.afficher());
    ui->tab_3->setAlternatingRowColors(true);
    ui->tab_3->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                             QTableView::item:selected { color: white; } \
                             QHeaderView::section { background-color: #769aa8; color: white; }");
                             ui->tab_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tab_3->verticalHeader()->setVisible(false);
    ui->tab_3->horizontalHeader()->setDefaultSectionSize(150);
    // f trie
    r_tmp.trie_tab_date(ui->tab_3, 1);

    //****GHAITH
    ui->lineEdit_Recherche->setPlaceholderText("Recherche...");
    QString styleSheet = "QLineEdit#lineEdit_Recherche {"
                         "  border: 2px solid gray;"
                         "  border-radius: 10px;"
                         "  padding: 5px;"
                         "  font-size: 16px;"
                         "  background-color: #f5f5f5;"
                         "}"
                         "QLineEdit#lineEdit_Recherche:focus {"
                         "  border: 2px solid blue;"
                         "}";
    ui->lineEdit_Recherche->setStyleSheet(styleSheet);

    ui->tableView_Machine->setModel(Mtmp.afficher());
    ui->tableView_Machine->setAlternatingRowColors(true);
    ui->tableView_Machine->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                                         QTableView::item:selected { color: white; } \
                                         QHeaderView::section { background-color: #769aa8; color: white; }");
                                         ui->tableView_Machine->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tableView_Machine->verticalHeader()->setVisible(false);
    ui->tableView_Machine->horizontalHeader()->setDefaultSectionSize(150);

    startAlertNotification();
    //////////////
    //****MAHMOUD
    ui->lineEdit_Recherche_2service->setPlaceholderText("Recherche...");
    QString styleSheetS = "QLineEdit#lineEdit_Recherche_2service {"
                          "  border: 2px solid gray;"
                          "  border-radius: 10px;"
                          "  padding: 5px;"
                          "  font-size: 16px;"
                          "  background-color: #f5f5f5;"
                          "}"
                          "QLineEdit#lineEdit_Recherche_2service:focus {"
                          "  border: 2px solid blue;"
                          "}";
    ui->lineEdit_Recherche_2service->setStyleSheet(styleSheetS);
    ui->tableView_2service->setModel(ser.afficher());
    ui->tableView_2service->setAlternatingRowColors(true);
    ui->tableView_2service->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                                          QTableView::item:selected { color: white; } \
                                          QHeaderView::section { background-color: #769aa8; color: white; }");
                                          ui->tableView_2service->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tableView_2service->verticalHeader()->setVisible(false);
    ui->tableView_2service->horizontalHeader()->setDefaultSectionSize(150);
    //****MOUNIR


    ui->chercher->setPlaceholderText("Recherche...");
    QString styleSheetC = "QLineEdit#chercher {"
                          "  border: 2px solid gray;"
                          "  border-radius: 10px;"
                          "  padding: 5px;"
                          "  font-size: 16px;"
                          "  background-color: #f5f5f5;"
                          "}"
                          "QLineEdit#chercher:focus {"
                          "  border: 2px solid blue;"
                          "}";
    ui->chercher->setStyleSheet(styleSheetC);
    ui->tableview_l->setModel(Ctmp.afficher());
    ui->tableview_l->setAlternatingRowColors(true);
    ui->tableview_l->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                                   QTableView::item:selected { color: white; } \
                                   QHeaderView::section { background-color: #769aa8; color: white; }");
                                   ui->tableview_l->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tableview_l->verticalHeader()->setVisible(false);
    ui->tableview_l->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableview_s->setModel(Ctmp.afficher());
    ui->tableview_m->setModel(Ctmp.afficher());
    ui->tableview_a->setModel(Ctmp.afficher());
    //fel Ajout
    ui->id_button->setValidator(new QIntValidator(0,999999999,this));
    ui->cap_button->setValidator(new QIntValidator(0,999999999,this));
    ui->nom_button->setValidator(new QRegExpValidator(QRegExp("[A-Z a-z]+"), this));
    //fel modif
    ui->id_mod_2->setValidator(new QIntValidator(0,999999999,this));
    ui->cap_buttonn->setValidator(new QIntValidator(0,999999999,this));
    ui->nom_buttonn->setValidator(new QRegExpValidator(QRegExp("[A-Z a-z]+"), this));

    //fel supp
    ui->id_supp->setValidator(new QIntValidator(0,999999999,this));

    //****ZIED
    ui->recherchervehicule->setPlaceholderText("Recherche...");
    QString styleSheetV = "QLineEdit#recherchervehicule {"
                          "  border: 2px solid gray;"
                          "  border-radius: 10px;"
                          "  padding: 5px;"
                          "  font-size: 16px;"
                          "  background-color: #f5f5f5;"
                          "}"
                          "QLineEdit#recherchervehicule:focus {"
                          "  border: 2px solid blue;"
                          "}";
    ui->recherchervehicule->setStyleSheet(styleSheetV);
    Vehicule v;
    ui->tableViewvehicule->setModel(v.afficher_vehicule());
    ui->tableViewvehicule->setAlternatingRowColors(true);
    ui->tableViewvehicule->setStyleSheet("QTableView { selection-background-color: blue; gridline-color: gray; } \
                                         QTableView::item:selected { color: white; } \
                                         QHeaderView::section { background-color: #769aa8; color: white; }");
                                         ui->tableViewvehicule->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            ui->tableViewvehicule->verticalHeader()->setVisible(false);
    ui->tableViewvehicule->horizontalHeader()->setDefaultSectionSize(150);
    connect(ui->tableViewvehicule, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_tableViewvehicule_clicked(const QModelIndex &)));
    //////////////
    // Arduino Setup
    // Emlpoi
    int ret = aEmp.connect_arduino();
    switch (ret)
    {
    case (0):
        qDebug() << "arduino is available and connected to :" << aEmp.getarduino_port_name();
        break;
    case (1):
        qDebug() << "arduino is available and not connected to :" << aEmp.getarduino_port_name();
        break;
    case (-1):
        qDebug() << "arduino not available.";
    }

    //RDV
    int retr = aRDV.connect_arduino();
    switch (retr)
    {
    case (0):
        qDebug() << "arduino is available and connected to :" << aRDV.getarduino_port_name();
        break;
    case (1):
        qDebug() << "arduino is available and not connected to :" << aRDV.getarduino_port_name();
        break;
    case (-1):
        qDebug() << "arduino not available.";
    }
    QObject::connect(aEmp.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
    QObject::connect(aRDV.getserial(), SIGNAL(readyRead()), this, SLOT(update_label_rdv()));
    //////
    // Create a "Log Out" button
    QPushButton* logoutButton = new QPushButton("Log Out", this);
    logoutButton->setStyleSheet("QPushButton {"
                                    "background-color: #FF5722;"
                                    "border: none;"
                                    "padding: 8px 16px;"
                                    "color: white;"
                                    "font-weight: bold;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #FF7043;"
                                    "}");

     logoutButton->setGeometry(10, 525, 100, 35);

    // Connect the "Log Out" button to the logout() slot
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::logout);
    /////
    // Create a "Close Application" button
    QPushButton* closeButton = new QPushButton("Close", this);
    closeButton->setStyleSheet("QPushButton {"
                                   "background-color: #FF5722;"
                                   "border: none;"
                                   "padding: 8px 16px;"
                                   "color: white;"
                                   "font-weight: bold;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #FF7043;"
                                   "}");

    closeButton->setGeometry(120, 525, 100, 35);

    // Connect the "Close Application" button to the close() slot
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::close);

}

void MainWindow::showTabForRole(QString role)
{
    // Define the available roles as a QStringList
    QStringList availableRoles = {"Employe", "Secretaire", "Mecanicien", "Technicien", "Admin"};

    // Define the available roles as a QMap
    QMap<QString, int> roles;
    roles["Employes"] = 0;
    roles["Secretaire"] = 1;
    roles["Mecanicien"] = 2;
    roles["Technicien"] = 3;
    roles["Admin"] = 4;

    // Check if the user is an admin
    if (role == "Admin") {
        // Show all tabs
        for (int i = 0; i < ui->tabWidget_Gestions->count(); i++) {
            ui->tabWidget_Gestions->setTabEnabled(i, true);
        }
    } else {
        // Hide all tabs
        for (int i = 0; i < ui->tabWidget_Gestions->count(); i++) {
            ui->tabWidget_Gestions->setTabEnabled(i, false);
        }

        // Show the appropriate tab based on the role
        switch (role.toLower().toStdString()[0]) {
        case 'e': // Employes
            ui->tabWidget_Gestions->setTabEnabled(0, true);
            ui->tabWidget_Gestions->setCurrentIndex(0);
            break;
        case 's': // Secretaire
            ui->tabWidget_Gestions->setTabEnabled(1, true);
            ui->tabWidget_Gestions->setCurrentIndex(1);
            ui->tabWidget_Gestions->setTabEnabled(5, true); // Vehicule
            break;
        case 'm': // Mecanicien
            ui->tabWidget_Gestions->setTabEnabled(2, true);
            ui->tabWidget_Gestions->setCurrentIndex(2);
            ui->tabWidget_Gestions->setTabEnabled(4, true); // Centre
            break;
        case 't': // Technicien
            ui->tabWidget_Gestions->setTabEnabled(3, true); // Service
            ui->tabWidget_Gestions->setCurrentIndex(3);
            break;
        default:
            // Handle invalid role
            break;
        }

    }
}

void MainWindow::loadingScreen(int showTime)
{
    QDialog* loadingDialog = new QDialog(this, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    loadingDialog->setWindowTitle(tr("Please Wait"));
    loadingDialog->setStyleSheet("background-color: #ffffff;");

    loadingDialog->setFixedSize(this->size());

    loadingDialog->move(qApp->desktop()->availableGeometry().center() - loadingDialog->rect().center());

    QLabel* loadingLabel = new QLabel(loadingDialog);
    QMovie* movie = new QMovie(":/images/icons/loading.gif");
    movie->setSpeed(250);
    loadingLabel->setMovie(movie);
    loadingLabel->setFixedSize(500, 500);
    loadingLabel->setAlignment(Qt::AlignCenter);

    QLabel* loadingMessage = new QLabel(loadingDialog);
    loadingMessage->setText(tr("Loading..."));
    loadingMessage->setStyleSheet("font-size: 16px; color: black;");
    loadingMessage->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(loadingLabel);
    layout->addWidget(loadingMessage);
    layout->setAlignment(Qt::AlignCenter);
    loadingDialog->setLayout(layout);

    loadingLabel->movie()->start();

    loadingDialog->show();
    QTime timer;
    timer.start();
    while(timer.elapsed() < showTime)
    {
        QCoreApplication::processEvents();
    }

    loadingLabel->movie()->stop();
    loadingDialog->close();
}

void MainWindow::authenticate()
{
    // Create a new authentification instance
    auth = new authentification();

    /////////////////////animation
    QPropertyAnimation* animation = new QPropertyAnimation(auth, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    auth->setWindowOpacity(0);
    ///////////////////////
    auth->setWindowFlags(Qt::CustomizeWindowHint);
    auth->setWindowTitle("Login");
    connect(auth, &authentification::loggedIn, this, &MainWindow::showTabForRole);
    auth->show();
    while (auth->isVisible())
    {
        qApp->processEvents();
    }
}

void MainWindow::logout()
{
    // Reset isAuthenticated to false
    isAuthenticated = false;
    aEmp.close_arduino();
    aRDV.close_arduino();
    // Call authenticate() to start the authentication process again
    authenticate();
}



MainWindow::~MainWindow()
{
    aEmp.close_arduino();
    aRDV.close_arduino();
    delete ui;
}

// supp
void MainWindow::on_pushButton_3_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int cin = index.data(Qt::DisplayRole).toInt();
    bool test = emp.supprimer_employe(cin); // appel de la methode supp via emp
    if (test)
    {
        ui->tableView->setModel(emp.afficher_employe()); // refresh

        QMessageBox::information(nullptr, QObject::tr("Supprimer un employe"),
                                 QObject::tr("Employe supprimé.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un employe"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}
// ajout
void MainWindow::on_pushButton_clicked()
{
    setEnabled(false);
    ajout_employes *a = new ajout_employes();
    a->show();
    while (a->isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableView->setModel(emp.afficher_employe());
}
// modifier
void MainWindow::on_pushButton_2_clicked()
{
    employe emp;
    QVariant rowData = ui->tableView->model()->data(ui->tableView->currentIndex());

    qDebug() << "La ligne sélectionnée est : " << rowData.toString();

    int g_CIN = rowData.toInt();

    setEnabled(false);
    modifier_employes modInterface(g_CIN, this);
    modInterface.show();

    while (modInterface.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);

    ui->tableView->setModel(emp.afficher_employe());
}
// refresh
void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(emp.afficher_employe()); // refresh
}

void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    ui->tableView->setModel(emp.recherche_employe(arg1));
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox->currentText() == "CIN CROISSANT")
        ui->tableView->setModel(emp.triCIN2());
    else if (ui->comboBox->currentText() == "CIN DECROISSANT")
        ui->tableView->setModel(emp.triCIN3());
}

void MainWindow::on_pushButton_5_clicked()
{
    emp.exporterpdf(ui->textBrowser);
}

void MainWindow::on_stat_clicked()
{
    stat_combo *s = new stat_combo();

    s->setWindowTitle("statistique");
    s->on_stat_clicked();
    s->show();
}

void MainWindow::on_calender_clicked()
{

    calender *c = new calender();

    c->setWindowTitle("calender");
    c->on_calender_clicked();

    c->show();
}

void MainWindow::on_pushButton_hist_clicked()
{
    historique *h = new historique();

    h->setWindowTitle("hist");
    h->on_pushButton_hist_clicked();
    h->show();
}

void MainWindow::update_label()
{
    data = aEmp.read_from_arduino();
    data_text += QString::fromStdString(data.toStdString());
    QSqlQuery query;
    if (data_text == " F3 29 DD 1B\r\n")
    {
        query.prepare("update RFID SET RFI ='BLOCKED'");
        query.exec();
        QSqlQuery query1;
        query1.prepare("select * from RFID");
        query1.exec();
        query1.next();
        QByteArray stat = query1.value(0).toByteArray();
        aEmp.write_to_arduino(stat);
        QMessageBox::critical(nullptr, QObject::tr("Gestion-Des-Employes"),
                              QObject::tr("      Access Denied!\n"
                                          "Taper sur cancel pour fermer."),
                              QMessageBox::Cancel);
        data = "";
        data_text = "";
    }
    else if (data_text == " B3 51 1D AD\r\n")
    {
        query.prepare("update RFID SET RFI ='PASSED'");
        query.exec();
        QSqlQuery query1;
        query1.prepare("select * from RFID");
        query1.exec();
        query1.next();
        QByteArray stat = query1.value(0).toByteArray();
        aEmp.write_to_arduino(stat);
        QMessageBox::information(nullptr, QObject::tr("Gestion-Des-Employes"),
                                 QObject::tr("Access Granted [mecanicien]!\n"
                                             "  Taper sur cancel pour fermer."),
                                 QMessageBox::Cancel);
        data = "";
        data_text = "";
    }

    else if (data_text == " 01 DF 8B 26\r\n")
    {
        query.prepare("update RFID SET RFI ='PASSED'");
        query.exec();
        QSqlQuery query1;
        query1.prepare("select * from RFID");
        query1.exec();
        query1.next();
        QByteArray stat = query1.value(0).toByteArray();
        aEmp.write_to_arduino(stat);
        QMessageBox::information(nullptr, QObject::tr("Gestion-Des-Employes"),
                                 QObject::tr("Access Granted [technicien]!\n"
                                             "  Taper sur cancel pour fermer."),
                                 QMessageBox::Cancel);
        data = "";
        data_text = "";
    }
}

void MainWindow::on_pushButton_ARDUINO_clicked()
{

    QSqlQuery query1;
    query1.prepare("select * from RFID");
    query1.exec();
    query1.next();
    QByteArray stat = query1.value(0).toByteArray();
    aEmp.write_to_arduino(stat);
}

//***********RANIA

void MainWindow::on_pushButton_Supp_clicked()
{
    RDV r;
    // Obtenez les données de cette cellule dans le modèle de données
    QVariant rowData = ui->tab_3->model()->data(ui->tab_3->currentIndex());

    // Affichez les données de la ligne sélectionnée dans la console
    qDebug() << "La ligne sélectionnée est : " << rowData.toString();

    bool test = r.supprimer(rowData.toInt());

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Suppression effectuee.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        ui->tab_3->setModel(r_tmp.afficher());
        // f trie
        r_tmp.trie_tab_date(ui->tab_3, 1);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Suppression non effectuee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::on_pushButton_Ajout_clicked()
{
    setEnabled(false);
    Ajouter_RDVs ajoutInterface(this);
    ajoutInterface.show();
    while (ajoutInterface.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tab_3->setModel(r_tmp.afficher());
    r_tmp.trie_tab_date(ui->tab_3, 1);
}

void MainWindow::on_pushButton_Mod_clicked()
{
    RDV r;
    QVariant rowData = ui->tab_3->model()->data(ui->tab_3->currentIndex());

    int g_ID_RDV = rowData.toInt();

    setEnabled(false);

    Modifier_RDV modInterface(g_ID_RDV, this);

    modInterface.show();

    while (modInterface.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);

    ui->tab_3->setModel(r_tmp.afficher());
    r_tmp.trie_tab_date(ui->tab_3, 1);
}

//*****Metier Recherche Centre

void MainWindow::on_lineEdit_recherche_2_textChanged(const QString &arg1)
{
    // proxy->setFilterFixedString(arg1);

    if (arg1 == "")
    {
        ui->tab_3->setModel(r_tmp.afficher());
        // f trie
        r_tmp.trie_tab_date(ui->tab_3, 1);
    }
    else
    {
        QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
        proxy->setSourceModel(ui->tab_3->model()); // `model` est le modèle source à filtrer
        proxy->setFilterFixedString(arg1);
        proxy->setFilterKeyColumn(2); // filtre les données de 3eme colonne
        ui->tab_3->setModel(proxy);   // la vue qui affiche les données filtrées
    }
}

//*****Metier PDF
void MainWindow::on_pushButton_pdf_clicked()
{
    r_tmp.export_pdf(ui->lineEdit_recherche->text(), ui->textBrowser);
}

//*****Metier stat Centre
void MainWindow::on_stat_2_clicked()
{
    stat_rdv *stat = new stat_rdv();

    stat->setWindowTitle("statistique Centre");
    stat->on_stat_clicked();
    stat->show();
}

void MainWindow::on_comboBox_rdv_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox_rdv->currentText() == "tous les RDV")
    {
        ui->tab_3->setModel(r_tmp.afficher());
        // f trie
        r_tmp.trie_tab_date(ui->tab_3, 1);
    }

    if (ui->comboBox_rdv->currentText() == "RDV reserve")
    {
        ui->tab_3->setModel(r_tmp.afficher_RDV_reserve());
        // f trie
        r_tmp.trie_tab_date(ui->tab_3, 1);
    }

    if (ui->comboBox_rdv->currentText() == "RDV non reserve")
    {
        ui->tab_3->setModel(r_tmp.afficher_RDV_non_reserve());
        // f trie
        r_tmp.trie_tab_date(ui->tab_3, 1);
    }
}

void MainWindow::on_Ajout_Auto_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select max(ID_RDV) as max_id from GESTION_RDVS");
    int max_id = model->data(model->index(0, 0)).toInt() + 1;

    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("CENTRE: Tunis / Ariena"), QLineEdit::Normal,
                                         "Tunis", &ok);

    if (ok && ((text == "Tunis") || (text == "Ariena")))
    {
        QString text_1 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                               tr("DATE :"), QLineEdit::Normal,
                                               "yyyy-MM-dd", &ok);
        QString format = "yyyy-MM-dd";
        QDateTime dt = QDateTime::fromString(text_1, format);

        if (ok)
        {
            QString text_2 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                   tr("Heure debut:"), QLineEdit::Normal,
                                                   "09:00", &ok);
            QString format = "HH:mm";
            QTime HD = QTime::fromString(text_2, format);

            if (ok)
            {
                QString text_3 = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                       tr("Heure Fin:"), QLineEdit::Normal,
                                                       "12:00", &ok);
                QString format = "HH:mm";
                QTime HF = QTime::fromString(text_3, format);

                r_tmp.Rdv_auto(max_id, dt, HD, HF, text);
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("Ajout effectuee.\n"
                                                     "Click Cancel to exit."),
                                         QMessageBox::Cancel);
                // afficher
                ui->tab_3->setModel(r_tmp.afficher());
                // f trie
                r_tmp.trie_tab_date(ui->tab_3, 1);
            }
        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Ajout non effectuee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::on_Affecter_Mat_clicked()
{
    bool ok;
    QString mat = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                        tr("MATRICULE:"), QLineEdit::Normal,
                                        "xxxTUNxxx", &ok);

    if (ok)
    {
        QModelIndex idx = ui->tab_3->model()->index(ui->tab_3->currentIndex().row(), 0);

        // Obtenez les données de cette cellule dans le modèle de données
        QVariant rowData = ui->tab_3->model()->data(idx);
        r_tmp.setMatricule(mat);
        // QModelIndex
        idx = ui->tab_3->model()->index(ui->tab_3->currentIndex().row(), 1); // ui->tab->currentIndex().column()+1);

        r_tmp.setDate(ui->tab_3->model()->data(idx).toDateTime());

        qDebug() << "row : " << ui->tab_3->model()->data(idx).toDateTime();

        int var = r_tmp.Affecter_Matricule(rowData.toInt());

        if (var == -1)
        {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("vehicule a ete controle moins dun an.\n"
                                              "Click Cancel to exit."),
                                  QMessageBox::Cancel);
        }
        if (var != 1)
        {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("Matricule n'existe pas dans la table vehicule.\n"
                                              "Click Cancel to exit."),
                                  QMessageBox::Cancel);
        }

        else
        {

            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Ajout effectuee.\n"
                                                 "Click Cancel to exit."),
                                     QMessageBox::Cancel);
            //************mailllll

            Smtp *smtp = new Smtp("rania.naouar@esprit.tn", "211JFT5407", "smtp.gmail.com", 465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
            smtp->sendMail("rania.naouar@esprit.tn", "rania.naouar@esprit.tn", "RDV", "Votre rendez-vous a été confirmé\n");

            //*************

            // afficher
            ui->tab_3->setModel(r_tmp.afficher());
            // f trie
            r_tmp.trie_tab_date(ui->tab_3, 1);
        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("operation abondonnee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::update_label_rdv()
{
    QSqlQuery query1;
    query1.prepare("SELECT count(*) FROM GESTION_RDVS");
    query1.exec();
    query1.next();
    QByteArray data1 = query1.value(0).toByteArray();
    qDebug() << data1;
    aRDV.write_to_arduino(data1);

    data = aRDV.read_from_arduino();
    data_text += QString::fromStdString(data.toStdString());

    // Détecter les mouvements des capteurs
    bool Entrez = false;
    bool Sortez = false;
    if (data_text.contains("Entrez"))
    {
        Entrez = true;
        QSqlQuery query;
        query.prepare("insert into ARDUINO (ETAT)"
                      "values (:ETAT)");
        query.bindValue(":ETAT", "Entrez");
        query.exec();
        data_text = "";
    }
    else if (data_text.contains("Sortez"))
    {
        Sortez = true;
        QSqlQuery query;
        query.prepare("insert into ARDUINO (ETAT)"
                      "values (:ETAT)");
        query.bindValue(":ETAT", "Sortez");
        query.exec();
        data_text = "";
    }

    if (Entrez)
    {
        QMessageBox::information(nullptr, QObject::tr("Vehicule"),
                                 QObject::tr("Entrez!\n"
                                             "Taper sur cancel pour fermer."),
                                 QMessageBox::Cancel);
    }
    else if (Sortez)
    {
        QMessageBox::information(nullptr, QObject::tr("Vehicule"),
                                 QObject::tr("Sortez!\n"
                                             "Taper sur cancel pour fermer."),
                                 QMessageBox::Cancel);
    }
}

//****GHAITH
void MainWindow::on_pushButton_MainAjout_clicked()
{
    setEnabled(false);
    AjouterMachine AM(this);
    AM.show();
    while (AM.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);

    ui->tableView_Machine->setModel(Mtmp.afficher());
}

void MainWindow::on_pushButton_MainModif_clicked()
{
    isAuthenticated=true;
    Machine M;
    QVariant rowData = ui->tableView_Machine->model()->data(ui->tableView_Machine->currentIndex());

    int ID_MACHINE = rowData.toInt();
    setEnabled(false);
    ModifierMachine modInterface(ID_MACHINE, this);
    modInterface.show();
    while (modInterface.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableView_Machine->setModel(Mtmp.afficher()); // Update model only if changes have been made
}

void MainWindow::on_pushButton_MainSupp_clicked()
{
    QModelIndex currentIndex = ui->tableView_Machine->currentIndex();
    if (!currentIndex.isValid())
    {
        QMessageBox::critical(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Veuillez sélectionner une ligne à supprimer."),
                              QMessageBox::Ok);
        return;
    }

    QVariant rowData = ui->tableView_Machine->model()->data(currentIndex);
    int id = rowData.toInt();

    QMessageBox::StandardButton confirmDelete = QMessageBox::question(this, "Confirmation",
                                                                      "Êtes-vous sûr de vouloir supprimer cette ligne ?", QMessageBox::Yes | QMessageBox::No);

    if (confirmDelete == QMessageBox::Yes)
    {
        bool success = Mtmp.supprimer(id);
        if (success)
        {
            QAbstractItemModel *model = ui->tableView_Machine->model();
            model->removeRow(currentIndex.row());

            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                     QObject::tr("Suppression effectuée.\n"
                                                 "Cliquez sur OK pour continuer."),
                                     QMessageBox::Ok);
            ui->tableView_Machine->setModel(Mtmp.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Cliquez sur Annuler pour continuer."),
                                  QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_lineEdit_Recherche_textChanged(const QString &arg1)
{
    ui->tableView_Machine->setModel(Mtmp.recherche_Machine(arg1));
}

void MainWindow::on_checkBox_TRI_stateChanged(int arg1)
{
    ui->tableView_Machine->setModel(Mtmp.tri_Machine(arg1));
}

void MainWindow::on_pushButton_Stat_clicked()
{
    setEnabled(false);
    StatMachine SM;
    SM.show();
    while (SM.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);

    ui->tableView_Machine->setModel(Mtmp.afficher());
}

void MainWindow::on_pushButton_PDF_clicked()
{
    Mtmp.exporterpdf(ui->textBrowser);
}

void MainWindow::on_pushButton_Video_clicked()
{
    setEnabled(false);
    VideoPlayer VM;
    VM.show();
    while (VM.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);

    ui->tableView_Machine->setModel(Mtmp.afficher());
}

void MainWindow::on_pushButton_Notification_clicked()
{
    setEnabled(false);
    MachineStatusWindow MSW;
    MSW.show();
    while (MSW.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);

    ui->tableView_Machine->setModel(Mtmp.afficher());
}

void MainWindow::startAlertNotification()
{
    m_machineStatusTimer = new QTimer(this);

    connect(m_machineStatusTimer, &QTimer::timeout, this, &MainWindow::checkMachineStatus);

    m_machineStatusTimer->setInterval(5000);

    m_machineStatusTimer->start();
}

void MainWindow::checkMachineStatus()
{
    QSqlQuery query;

    if (!query.exec("SELECT COUNT(*) FROM GESTION_MACHINES WHERE ETAT = 'En panne'"))
    {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    if (query.next())
    {
        int numMachinesEnPanne = query.value(0).toInt();

        if (numMachinesEnPanne != m_lastNumMachinesEnPanne || m_deletedMachine)
        {
            if (numMachinesEnPanne > 0 && !m_machineAlertShown)
            {
                QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
                trayIcon->setIcon(QIcon(":/icons/alert.png"));
                trayIcon->show();
                trayIcon->showMessage("Machine Alert", QString("%1 machine(s) en panne(s)!").arg(numMachinesEnPanne), QSystemTrayIcon::Warning);
                m_machineAlertShown = true;
            }
            else if (numMachinesEnPanne == 0 && m_machineAlertShown)
            {
                QSystemTrayIcon *trayIcon = qobject_cast<QSystemTrayIcon *>(sender());
                if (trayIcon)
                {
                    trayIcon->hide();
                }
                m_machineAlertShown = false;
            }

            m_lastNumMachinesEnPanne = numMachinesEnPanne;

            m_deletedMachine = false;
        }
    }

    query.clear();
    query.finish();
}

void MainWindow::stopAlertNotification()
{
    if (m_machineStatusTimer)
    {
        m_machineStatusTimer->stop();
        delete m_machineStatusTimer;
        m_machineStatusTimer = nullptr;
    }

    if (m_machineAlertShown)
    {
        QSystemTrayIcon *trayIcon = qobject_cast<QSystemTrayIcon *>(sender());
        if (trayIcon)
        {
            trayIcon->hide();
        }
        m_machineAlertShown = false;
    }

    m_lastNumMachinesEnPanne = 0;
}

//****MAHMOUD
void MainWindow::on_pushButton_MainAjout_2service_clicked()
{
    setEnabled(false);
    addservice AM(this);
    AM.show();
    while (AM.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableView_2service->setModel(ser.afficher());
}

void MainWindow::on_pushButton_MainModif_2service_clicked()
{
    Service M;
    QVariant rowData = ui->tableView_2service->model()->data(ui->tableView_2service->currentIndex());

    qDebug() << "La ligne sélectionnée est : " << rowData.toString();

    int g_ID_SERVICE = rowData.toInt();

    setEnabled(false);

    Modifservice modInterface(g_ID_SERVICE,this);
    modInterface.show();

    while (modInterface.isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableView_2service->setModel(ser.afficher());
}

void MainWindow::on_pushButton_MainSupp_2service_clicked()
{
    Service M;
    QVariant rowData = ui->tableView_2service->model()->data(ui->tableView_2service->currentIndex());
    qDebug() << "La ligne sélectionnée est : " << rowData.toString();
    bool test = M.supprimer(rowData.toInt());
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Suppression effectuee.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);


        ui->tableView_2service->setModel(ser.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("Suppression non effectuee.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
}

void MainWindow::on_lineEdit_Recherche_2service_textEdited(const QString &arg1)
{
    ui->tableView_2service->setModel(ser.recherche_Service(arg1));
}

void MainWindow::on_checkBox_TRI_2service_stateChanged(int arg1)
{
    ui->tableView_2service->setModel(ser.tri_service(arg1));

}

void MainWindow::on_pushButton_Mainenvoyerservicepdf_clicked()
{
    ser.exporterpdf(ui->textBrowser_4);
}

void MainWindow::on_pushButton_Mainstatservice_clicked()
{
    statservice modInterface(this);
    modInterface.show();

    while (modInterface.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);

}

///messagerie
void MainWindow::on_pushButton_Mainstat_2_clicked()
{

    setEnabled(false);
    lanmessage AM(this);
    AM.show();
    while (AM.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);

}

void MainWindow::on_remise_clicked()
{
    setEnabled(false);
    fidele2 AM(this);
    AM.show();
    while (AM.isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);
}

//****MOUNIR
void MainWindow::on_ajouterB_clicked()
{
    int id_centre;
    int capacite;
    QString nom_centre;
    QString adr;
    QMessageBox messagebox;
    nom_centre=ui->nom_button->text();
    adr=ui->comboBox->currentText();
    id_centre=ui->id_button->text().toInt();
    capacite=ui->cap_button->text().toInt();

    /////////////////////////////verification de l'ajout/////////////////////////////////////////////////////////

    Centre c(id_centre,nom_centre,adr,capacite);
    bool test=c.ajouter();

    if(test)

    { messagebox.information(nullptr, messagebox.tr("Succès"), messagebox.tr("Ajout effectué"));
    }
    else
        messagebox.critical(nullptr, messagebox.tr("Echec"), messagebox.tr("Ajout non effectué"));

    ui->id_button->clear();//if ajout non affectué alors la "lineedit de identifiant " sera supprimée
    ui->nom_button->clear();
    ui->cap_button->clear();


    //affichage
    ui->tableview_a->setModel(c.afficher());
    ui->tableview_l->setModel(c.afficher());
}

void MainWindow::on_modifierB_clicked()
{
    int id_centre = ui->id_mod_2->text().toInt();
    QString nom_centre = ui->nom_buttonn->text();
    QString adr = ui->comboBox_2->currentText();
    int capacite = ui->cap_buttonn->text().toInt();

    Centre c(id_centre,nom_centre,adr,capacite);
    bool test = c.modifier(id_centre);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("modification"),
                                 QObject::tr("service modifié.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

        ui->tableview_m->setModel(c.afficher());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                              QObject::tr("problème de modification.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimerB_clicked()
{
    int id_centre;
    Centre c;
    QMessageBox messagebox;
    id_centre=ui->id_supp->text().toInt();

    bool test=c.supprimer(id_centre);
    if(test)

    { messagebox.information(nullptr, messagebox.tr("Succès"), messagebox.tr("suppression effectué"));
    }
    else
        messagebox.critical(nullptr, messagebox.tr("Echec"), messagebox.tr("suppression non effectué"));


    ui->id_supp->clear();

    ui->tableview_s->setModel(c.afficher());
}

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    ui->tableview_l->setModel(Ctmp.rechercher(arg1));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->tableview_l->setModel(Ctmp.tri(arg1));
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableview_l->model()->rowCount();
    const int columnCount =ui->tableview_l->model()->columnCount();


    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>Welcome to Visita</title>\n").arg("eleve")
          <<  "</head>\n"
              "<body bgcolor=#d3e0ea link=#5000A0>\n"
              "<h1>Liste des Centres</h1>"

              "<table border=1 cellspacing=0 cellpadding=2 style='margin-left:auto ,margin-right auto width:70%;'>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableview_l->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableview_l->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableview_l->isColumnHidden(column)) {
                QString data = ui->tableview_l->model()->data(ui->tableview_l->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";



    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);


    //QTextDocument document;
    //document.setHtml(html);
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", ".", "PDF files (*.pdf)");
    if (!fileName.isEmpty()) {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        document->print(&printer);
    }


    cout<<"Done !\n"<<endl;
}

void MainWindow::on_statttttt_clicked()
{
    using namespace std;
    double s1=0.0,s2=0.0,s3=0.0;
    QSqlQuery query , q1,q2,q3;
    query.exec("SELECT capacite FROM gestion_centres");

    vector<int> capacites;


    int total = 0;
    while (query.next()) {
        int capacite = query.value(0).toInt();
        capacites.push_back(capacite);
        total += capacite;
    }

    //ta3tik el nb totale des chercheurs eli 3marhom mabin 0 w 18
    q1.prepare("SELECT count (*)  from gestion_centres where capacite  between 0 and 18 " );

    q1.exec();
    if (q1.next()) {
        s1= q1.value(0).toInt();}


    q2.prepare("SELECT count (*)  from gestion_centres where capacite between 19 and 60 " );

    q2.exec();
    if (q2.next()) {
        s2= q2.value(0).toInt();}


    q3.prepare("SELECT count (*)  from gestion_centres where capacite >60 " );

    q3.exec();
    if (q3.next()) {
        s3= q3.value(0).toInt();}

    //Les pourcentages::

    float a1 = (s1/total)*100;
    float a2 = (s2/total)*100;
    float a3 = (s3/total)*100;



    // Calcul des statistiques
    int n = capacites.size();
    double mean = static_cast<double>(total) / n;

    double sum_of_squared_diff = 0;
    for (int i = 0; i < n; i++) {
        sum_of_squared_diff += pow(capacites[i] - mean, 2);
    }

    QPieSeries *series = new QPieSeries();
    //series->append("nombre totale des chercheurs ", total);
    series->append("le % de capacites entre 0 t 18 ",  a1);
    series->append("le % de capacites entre 19 t 60 ",  a2);
    series->append("le % de capacites est sup de 60 ",  a3);


    QChart *chart = new QChart(); //création du cercle
    chart->addSeries(series);
    chart->setTitle("statistique  des capacites");


    QColor colors[] = {Qt::red, Qt::green, Qt::blue};

    for (int i = 0; i < series->count(); i++) {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setBrush(colors[i % 3]);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1268,748);
    chartView->setRenderHint(QPainter::Antialiasing); // Enable antialiasing


    chartView->show();
}

//****ZIED
void MainWindow::on_tableViewvehicule_clicked(const QModelIndex &index)
{
    if (index.isValid()){
        selected=index.row();
    }
}

void MainWindow::on_pushButtonvehicule_clicked()
{
    setEnabled(false);
    Ajouter * window =new Ajouter;
    window->show();
    while (window->isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableViewvehicule->setModel(Vtmp.afficher_vehicule());
}

void MainWindow::on_pushButtonvehicule_supprimer_clicked()
{

    if(selected == -1)
    {

        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Rien n'est selectioné.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    Vehicule v;
    QSqlQueryModel * model = v.afficher_vehicule();
    QString matricule = model->record(selected).value("MATRICULE").toString();
    qDebug()<<matricule;

    if(v.supprimer_vehicule(matricule))
        qDebug()<<"success";
    else qDebug()<<"erreur";

    ui->tableViewvehicule->setModel(v.afficher_vehicule());

    selected = -1;

}

void MainWindow::on_pushButtonvehicule_modifier_clicked()
{
    if(selected == -1)
    {

        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Rien n'est selectioné.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    QString MATRICULE = ui->tableViewvehicule->model()->index(selected,0).data().toString();
    QString TYPE_V = ui->tableViewvehicule->model()->index(selected,1).data().toString();
    QString MARQUE = ui->tableViewvehicule->model()->index(selected,2).data().toString();
    QString N_CHASSIS = ui->tableViewvehicule->model()->index(selected,3).data().toString();

    Vehicule *v = new Vehicule(MATRICULE,TYPE_V,MARQUE,N_CHASSIS);
    selected = -1;
    setEnabled(false);
    modifier * window =new modifier(nullptr,v);
    window->show();
    while (window->isVisible())
    {
        qApp->processEvents();
    }
    loadingScreen(2000);
    setEnabled(true);
    ui->tableViewvehicule->setModel(Vtmp.afficher_vehicule());
}

void MainWindow::on_pushButtonvehicule_recherche_clicked()
{
    QString rechercher = ui->recherchervehicule->text();

    Vehicule v;

    if(rechercher == "")
    {
        ui->tableViewvehicule->setModel(v.afficher_vehicule());
    }
    else
    {
        int typeDuRecherche = ui->comboBoxvehicule->currentIndex();
        switch (typeDuRecherche) {
        case 0:
            ui->tableViewvehicule->setModel(v.rechercher_vehicule_matricule(rechercher));
            break;
        case 1:
            ui->tableViewvehicule->setModel(v.rechercher_vehicule_type(rechercher));
            break;
        case 2:
            ui->tableViewvehicule->setModel(v.rechercher_vehicule_marque(rechercher));
            break;
        case 3:
            ui->tableViewvehicule->setModel(v.rechercher_vehicule_num_chassis(rechercher));
            break;

        }
    }
}

void MainWindow::on_pushButtonvehicule_stat_clicked()
{
    setEnabled(false);
    statistique * window = new statistique;
    window->show();
    while (window->isVisible())
    {
        qApp->processEvents();
    }
    setEnabled(true);
    ui->tableViewvehicule->setModel(Vtmp.afficher_vehicule());
}

void MainWindow::on_pushButtonvehicule_pdf_clicked()
{
    Vehicule v;
    v.exporterPdf(ui->textBrowservehicule);
}

void MainWindow::on_TRIvehicule_stateChanged(int arg1)
{
    ui->tableViewvehicule->setModel(Vtmp.tri(arg1));
}
//////////////

