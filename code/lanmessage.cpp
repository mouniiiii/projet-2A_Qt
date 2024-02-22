#include "lanmessage.h"
#include "ui_lanmessage.h"
#include <QtCore>
#include <QMainWindow>
#include <QLineEdit>
#include "peer.h"
#include "dialognickname.h"
#include "messenger.h"
#include "pmwindow.h"

lanmessage::lanmessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lanmessage)
{
    ui->setupUi(this);
    msgr = new Messenger(this);
    DialogNickName *dlgName = new DialogNickName(this);
    connect(dlgName, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(msgr, SIGNAL(peersUpdated()), this , SLOT(onUpdateList()));
    connect(msgr, SIGNAL(roomListUpdated(QString,QString)), this, SLOT(onRoomListUpdated(QString,QString)));
    connect(msgr, SIGNAL(receivedPM(QString,QString)), this, SLOT(onReceivedPM(QString,QString)));
    dlgName->setModal(true);
    dlgName->setWindowTitle("Votre nom SVP!!");
    dlgName->show();
}

lanmessage::~lanmessage()
{
    delete ui;
}

void lanmessage::onSetName(QString name)
{
    msgr->setName(name);
    ui->lblWelcome->setText("Bienvenue " + msgr->Name());
    msgr->start();
}

void lanmessage::onUpdateList()
{
    ui->listUsers->clear();
    QList<Peer>& peers = msgr->getPeers();
    for(int i=0; i<peers.count(); i++)
        ui->listUsers->addItem(peers[i].ID());
}

void lanmessage::on_listUsers_doubleClicked(const QModelIndex &index)
{
    QString userid = ui->listUsers->currentItem()->text();
    makePMWindow(userid);
}
PMWindow* lanmessage::makePMWindow(QString title)
{
    if(pms.keys().contains(title))
    {
        pms[title]->setFocus();
        return pms[title];
    }
    else
    {
        PMWindow* newpm = new PMWindow();
        pms.insert(title, newpm);
        pmr.insert(newpm, title);
        connect(newpm, SIGNAL(enteredText(QString)), this, SLOT(onPMSend(QString)));
        connect(newpm, SIGNAL(closedWindow()), this, SLOT(onPMClosed()));
        newpm->setWindowTitle(title);
        newpm->show();
        return newpm;
    }
}

void lanmessage::onPMSend(QString text)
{
    PMWindow* to = qobject_cast<PMWindow*>(sender());
    msgr->sendPM(text, pmr[to]);
}

void lanmessage::onPMClosed()
{
    PMWindow* window = qobject_cast<PMWindow*>(sender());
    //msgr->sendPM("Closed chat window.", pmr[window]);
    pms.remove(pmr[window]);
    pmr.remove(window);
}

void lanmessage::onReceivedPM(QString from, QString text)
{
    makePMWindow(from)->receivedPM(text);
}

