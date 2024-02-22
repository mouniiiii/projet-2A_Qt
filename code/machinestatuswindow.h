#ifndef MACHINESTATUSWINDOW_H
#define MACHINESTATUSWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include "machine.h"
#include <QTimer>
#include <QToolTip>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QGraphicsItem>
#include "arduino_employe.h"

namespace Ui {
class MachineStatusWindow;
}

class MachineStatusWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MachineStatusWindow(QWidget *parent = nullptr);
    ~MachineStatusWindow();
    bool getMachineId(int index, const QString& state, QString& machineId);
private slots:
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
        // ce slot est lancé à chaque réception d'un message de Arduino
    void handleButtonClick();

private:
    Ui::MachineStatusWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsRectItem* keyRect;
    QLabel* keyLabel;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};



#endif // MACHINESTATUSWINDOW_H
