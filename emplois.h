#ifndef EMPLOIS_H
#define EMPLOIS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class emplois
{
public:
    emplois();
    emplois(int,QString,QString );
    int get_id_emplois();
    QString get_date_emplois();
    QString get_matiere();
    bool ajouter_em();
    QSqlQueryModel *  afficher_em();
    bool supprimer_em(int );
    bool modifier_em();
    QSqlQueryModel * chercher_ep(QString);
    QSqlQueryModel * trier_idAsc2();
    QSqlQueryModel * trier_idDesc2();
    QSqlQueryModel * Find_Emploi(QString);




private:
    int id_emplois;
    QString date_emplois,matiere;
};

#endif // EMPLOIS_H
