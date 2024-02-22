#ifndef AJOUTER_RDVS_H
#define AJOUTER_RDVS_H

#include <QMainWindow>

namespace Ui
{
    class Ajouter_RDVs;
}

class Ajouter_RDVs : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ajouter_RDVs(QWidget *parent = nullptr);
    ~Ajouter_RDVs();

private:
    Ui::Ajouter_RDVs *ui;

private slots:
    void on_pushButton_2_clicked();
};

#endif // AJOUTER_RDVS_H
