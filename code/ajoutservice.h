#ifndef AJOUTSERVICE_H
#define AJOUTSERVICE_H

namespace Ui {
class ajoutservice
{



    class Ajouterservice : public QDialog
    {
        Q_OBJECT

    public:
        explicit Ajouterservice(QWidget *parent = nullptr);
        ~Ajouterservice();

    private:
        Ui::Ajouterservice *ui;
    };
public:
    ajoutservice();
};

#endif // AJOUTSERVICE_H
