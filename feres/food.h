#ifndef FOOD_H
#define FOOD_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class food
{
public:
    food();
    food(int,QString,QString,QString,QString); // constructeur parametré
    QString get_entree();
    QString get_principale();
    QString get_dessert();
    QString get_jour();
    int get_id();
    bool ajouter(); // ajouter
    QSqlQueryModel * afficher(); // afficher
    bool supprimer(QString); // supprimer
    QSqlQueryModel * trier_id();
    QSqlQueryModel * trier_plat();
    QSqlQueryModel * trier_jour();
    QSqlQueryModel *chercher(const QString &);
    //bool modifier();
    bool update();
private:
    QString entree,principale,dessert,jour;
    int id;
};

#endif // FOOD_H
