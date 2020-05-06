#ifndef CLUBS_H
#define CLUBS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Clubs
{public:
    Clubs();
    Clubs(int,QString,QString,int,int,int);
    QString get_nom();
    QString get_type();
    int get_id();
    int get_idSalle();
    int get_idEmploye();
    int get_idEmplois();
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
    QString type;
    int idSalle;
    int idEmplois;
    int idEmploye;

};


#endif // CLUBS_H
