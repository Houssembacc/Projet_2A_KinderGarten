#ifndef CLASSE_H
#define CLASSE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class classe
{
public:
    classe();
    classe(int,QString); // constructeur parametré
    QString get_type();
    int get_ref();
    bool ajouter_classe(); // ajouter un etudiant
    QSqlQueryModel * afficher_classe(); // afficher l'etudiant ...
    bool supprimer_classe(int); // supprimer l'etudiant ...
    bool update_classe();
    QSqlQueryModel * trier_id();
    QSqlQueryModel * trier_type();
    QSqlQueryModel *recherchertype(const QString &);
private: // les attributs
    QString type;
    int ref;
};

#endif // CLASSE_H
