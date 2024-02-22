#ifndef MODIFIER_EMPLOYES_H
#define MODIFIER_EMPLOYES_H

#include <QMainWindow>

namespace Ui
{
    class modifier_employes;
}

class modifier_employes : public QMainWindow
{
    Q_OBJECT

    /*signals:
        void entry_added(); */

public:
    explicit modifier_employes(int cin, QWidget *parent = nullptr);
    ~modifier_employes();

private slots:
    void on_pushButton_clicked();

private:
    Ui::modifier_employes *ui;
};

#endif // MODIFIER_EMPLOYES_H
