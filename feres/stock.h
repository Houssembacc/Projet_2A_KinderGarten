#ifndef STOCK_H
#define STOCK_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class stock
{
public:
    stock();
    stock(QString,QString,QString,int); // constructeur parametré
    QString get_id();
    QString get_nom();
    QString get_type();
    int get_qte();
    //QDate get_lim();
    bool ajouter(); // ajouter
    QSqlQueryModel * afficher(); // afficher
    bool supprimer(QString); // supprimer
    bool update();
    QSqlQueryModel *chercher(const QString &);
    QSqlQueryModel * trier_type();
    QSqlQueryModel * trier_qte();
    QSqlQueryModel * trier_nom();
private:
    QString id,nom,type;
    int qte;
    //QDate lim;
};

#endif // STOCK_H
