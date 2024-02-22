#ifndef MODIFIERSERVICE_H
#define MODIFIERSERVICE_H

#include <QDialog>

namespace Ui {
class ModifierService;
}

class ModifierService : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierService(int id,QWidget *parent = nullptr);
    ~ModifierService();

private slots:
    void on_pushButton_Modifier_clicked();

private:
    Ui::ModifierService *ui;
};

#endif // MODIFIERSERVICE_H
