#ifndef MODIFIER_RDV_H
#define MODIFIER_RDV_H

#include <QMainWindow>

namespace Ui
{
    class Modifier_RDV;
}

class Modifier_RDV : public QMainWindow
{
    Q_OBJECT

public:
    // explicit Modifier_RDV(QWidget *parent = nullptr);

    explicit Modifier_RDV(int id, QWidget *parent = nullptr);
    ~Modifier_RDV();

private slots:
    void on_pushButton_mod_clicked();

private:
    Ui::Modifier_RDV *ui;
};

#endif // MODIFIER_RDV_H
