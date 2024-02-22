#ifndef LANMESSAGE_H
#define LANMESSAGE_H
#include <QtCore>
#include <QMainWindow>
#include <QLineEdit>
#include "peer.h"
#include "dialognickname.h"
#include "messenger.h"
#include "pmwindow.h"

#include <QDialog>

namespace Ui {
class lanmessage;
}

class lanmessage : public QDialog
{
    Q_OBJECT

public:
    explicit lanmessage(QWidget *parent = nullptr);
    ~lanmessage();
private slots:
    void onSetName(QString name);
    void onUpdateList();

    void onPMSend(QString text);
    void onPMClosed();


    void on_listUsers_doubleClicked(const QModelIndex &index);
    void onReceivedPM(QString from, QString text);


private:
    Ui::lanmessage *ui;
    Messenger* msgr;
    QMap<QString, PMWindow*> pms;
    QMap<PMWindow*, QString> pmr;

    PMWindow* makePMWindow(QString title);

};

#endif // LANMESSAGE_H
