#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Equipement
{public:
    Equipement();
    Equipement(int,QString,int,int,int);
    QString get_nom();
    int get_id();
    int get_idSalle();
    int get_idClub();
    int get_quantite();
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
    QString nom;
    int id;
    int quantite;
    int idClub;
    int idSalle;
};

#endif // EQUIPEMENT_H
