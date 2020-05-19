#ifndef BATIMENT_H
#define BATIMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class batiment
{
public:
    batiment();
    batiment(int,int,QString);
    int get_id();
    int get_nb();
    QString get_nom();
    bool ajouter();
    QSqlQueryModel *  afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* trier_nomasc();
    QSqlQueryModel* trier_nomdesc();
    QSqlQueryModel* trier_idasc();
    QSqlQueryModel* trier_iddesc();
    QSqlQueryModel* trier_nbetageasc();
    QSqlQueryModel* trier_nbetagedesc();
    QSqlQueryModel *rechercherparnom(const QString &);
    QSqlQueryModel *Find_batiment(QString );
private:
    int id,nbetage;
    QString nom;

};

#endif // BATIMENT_H
