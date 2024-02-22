#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//****NOUR
#include "employe.h"
#include "ajout_employes.h"
#include "modifier_employes.h"
#include "authentification.h"
#include "historique.h"
#include <QCalendarWidget>
#include <QMainWindow>
#include "arduino_employe.h"

//****Rania
#include "rdv.h"
#include "ajouter_rdvs.h"
#include "QTableView"
#include "rdv_arduino.h"

//****GHAITH
#include "machine.h"
#include <QDebug>
#include <QMessageBox>
#include "ajoutermachine.h"
#include "modifiermachine.h"
#include "statmachine.h"
#include "videoplayer.h"
#include "machinestatuswindow.h"
#include <QStandardItemModel>

//****MAHMOUD
#include "addservice.h"
#include "modifservice.h"
#include "service.h"
#include "messagerie.h"
#include "statservice.h"
#include "lanmessage.h"
#include "fidele2.h"
#include <QtCharts>

//****MOUNIR
#include <QApplication>
#include <iostream>
#include "centre.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QTextDocument>
#include <QChartView>
//****ZIED
#include "vehicule.h"
#include "ajouter.h"
#include "vehicule.h"
#include "modifier.h"
#include "statistique.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *getUi() { return ui; };
    void startAlertNotification();
    void checkMachineStatus();
    void stopAlertNotification();
    ////
    void loadingScreen(int);
    void alignNewWindow(QWidget *newWindow);
    ~MainWindow();

private slots:
    void logout();
    //****NOUR
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked(); // modif
    void on_pushButton_4_clicked();
    void on_lineEdit_recherche_textChanged(const QString &arg1);// recherce
    void on_comboBox_currentTextChanged(const QString &arg1);// tri
    void on_pushButton_5_clicked(); // pdf
    void on_stat_clicked();
    void on_calender_clicked();
    void on_pushButton_hist_clicked();
    void update_label();
    void on_pushButton_ARDUINO_clicked();

    //********Rania
    void on_pushButton_Ajout_clicked();
    void on_pushButton_Supp_clicked();
    void on_pushButton_Mod_clicked();
    void on_lineEdit_recherche_2_textChanged(const QString &arg1);
    void on_pushButton_pdf_clicked();
    void on_stat_2_clicked();
    void on_comboBox_rdv_currentTextChanged(const QString &arg1);
    void on_Ajout_Auto_clicked();
    void on_Affecter_Mat_clicked();
    void update_label_rdv();    // Arduino

    //****GHAITH
    void on_pushButton_MainAjout_clicked();
    void on_pushButton_MainModif_clicked();
    void on_pushButton_MainSupp_clicked();
    void on_lineEdit_Recherche_textChanged(const QString &arg1);
    void on_checkBox_TRI_stateChanged(int arg1);
    void on_pushButton_Stat_clicked();
    void on_pushButton_PDF_clicked();
    void on_pushButton_Video_clicked();
    void on_pushButton_Notification_clicked();
    void showTabForRole(QString role);

    //****MAHMOUD
    void on_pushButton_MainAjout_2service_clicked();
    void on_pushButton_MainModif_2service_clicked();
    void on_pushButton_MainSupp_2service_clicked();
    void on_remise_clicked();
    void on_pushButton_Mainstat_2_clicked();
    void on_pushButton_Mainenvoyerservicepdf_clicked();
    void on_pushButton_Mainstatservice_clicked();
    void on_checkBox_TRI_2service_stateChanged(int arg1);
    void on_lineEdit_Recherche_2service_textEdited(const QString &arg1);
    void on_tableViewvehicule_clicked(const QModelIndex &index);
    //void on_stat_3_clicked();

    //****MOUNIR
    void on_ajouterB_clicked();
    void on_modifierB_clicked();
    void on_supprimerB_clicked();
    void on_chercher_textChanged(const QString &arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_pdf_clicked();
    void on_statttttt_clicked();

    //****ZIED
    void on_pushButtonvehicule_clicked();
    void on_pushButtonvehicule_supprimer_clicked();
    void on_pushButtonvehicule_modifier_clicked();
    void on_pushButtonvehicule_recherche_clicked();
    void on_pushButtonvehicule_pdf_clicked();
    void on_pushButtonvehicule_stat_clicked();
    void on_TRIvehicule_stateChanged(int arg1);
private:
    Ui::MainWindow *ui;
    static bool isAuthenticated;
    void authenticate();
    //****NOUR
    employe emp;
    QCalendarWidget c;
    authentification *auth;
    historique h;
    //****ARDUINO
    QByteArray data;
    Arduino aEmp;
    Arduino aRDV;
    QString data_text;
    //****RANIA
    RDV r_tmp;
    //****GHAITH
    Machine Mtmp;
    bool m_machineAlertShown = false;
    bool m_deletedMachine = true;
    QTimer* m_machineStatusTimer;
    int m_lastNumMachinesEnPanne;
    //****MAHMOUD
    Service ser;
    QChartView *chartView;
    //****MOUNIR
    Centre Ctmp;
    //****ZIED
    int selected =-1;
    Vehicule Vtmp;
};
#endif // MAINWINDOW_H
