#ifndef MENAGE_H
#define MENAGE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Menage
{public:
    Menage();
    Menage(int,QString,QString,QString);
    QString get_nom();
    QString get_type();
    QString get_duree();
    int get_idSalle();
    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel * chercher(QString);
    QSqlQueryModel * trier_nomAsc();
    QSqlQueryModel * trier_nomDesc();
    QSqlQueryModel * trier_idAsc();
    QSqlQueryModel * trier_idDesc();
private:
    QString nomEmploye;
    int idSalle;
    QString typeProduits;
    QString Duree;
};

#endif // MENAGE_H
