#ifndef AJOUTER_H
#define AJOUTER_H

#include <QMainWindow>

namespace Ui {
class Ajouter;
}

class Ajouter : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ajouter(QWidget *parent = nullptr);
    ~Ajouter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Ajouter *ui;
};

#endif // AJOUTER_H
