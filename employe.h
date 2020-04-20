#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employe
{
public:
    employe();
    employe(int,QString,QString,QString,QString,int,QString);
    int get_id();
    QString get_nom();
    QString get_prenom();
    QString get_sexe();
    QString get_date_naissance();
    int get_cin();
    QString get_adresse();
    bool ajouter();
    QSqlQueryModel *  afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * chercher(QString );
    QSqlQueryModel * trier_nomAsc();
    QSqlQueryModel * trier_nomDesc();
    QSqlQueryModel * trier_idAsc();
    QSqlQueryModel * trier_idDesc();
    QSqlQueryModel * Find_Employe(QString );
    void check_login(QString ,QString );

private:
    int id_employe,cin_employe;
    QString nom_employe,prenom_employe,sexe,adresse_employe,date_naissance_employe;

};

#endif // EMPLOYE_H
