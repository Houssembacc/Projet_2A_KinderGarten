#ifndef PAYEMENT_H
#define PAYEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Payement
{
public:
    Payement();
    Payement(int,int,int,QString,QString);
    int get_id();
    int get_prix();
    QString get_date();
    QString get_type();
    int get_ideleve();

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_affectation();
    bool supprimer(int);
    bool update();
    QSqlQueryModel * trier_nom();
    QSqlQueryModel * trier_prenom();
    QSqlQueryModel * trier_id_eleve_asc();
    QSqlQueryModel * trier_id_eleve_desc();
    QSqlQueryModel *recherchernom(const QString &);
private:
    QString type,date;
    int id,id_eleve_fk,prix;
};

#endif // PAYEMENT_H
