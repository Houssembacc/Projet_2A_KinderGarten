#ifndef ELEVE_H
#define ELEVE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Eleve
{
public:
    Eleve();
    Eleve(int,QString,QString,QString,QString,QString,int); // constructeur parametré
    QString get_nom();
    QString get_prenom();
    QString get_adresse();
    QString get_date_naissance();
    int get_id();
    int get_reference();
    bool ajouter(); // ajouter un etudiant
    QSqlQueryModel * afficher(); // afficher l'etudiant ...
    bool supprimer(int); // supprimer l'etudiant ...
    bool update();
    QSqlQueryModel * trier_nom();
    QSqlQueryModel * trier_prenom();
    QSqlQueryModel * trier_id_eleve_asc();
    QSqlQueryModel * trier_id_eleve_desc();
    QSqlQueryModel *recherchernom(const QString &);
private: // les attributs
    QString nom,prenom,adresse,datenaissance,sexe;
    int id,reference;
};

#endif // ELEVE_H
