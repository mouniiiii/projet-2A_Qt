#ifndef FIDELE2_H
#define FIDELE2_H

#include <QDialog>
#include "service.h"
namespace Ui {
class fidele2;
}

class fidele2 : public QDialog
{
    Q_OBJECT

public:
    explicit fidele2(QWidget *parent = nullptr);
    ~fidele2();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_toggled(bool checked);

    void on_checkBox_pressed();

private:
    Ui::fidele2 *ui;
    Service ser;
};

#endif // FIDELE2_H
