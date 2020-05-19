#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class salle
{
public:
    salle();
    salle(int,QString,int,int,int,int,QString,int);
    int get_idsalle();
    int get_idbat();
    int get_etage();
    QString get_etat();
    int get_nbeleve();
    QString get_nomsalle();
    bool ajoutersalle();
    QSqlQueryModel *  affichersalle();
    bool supprimersalle(int);
    bool modifier();
    QSqlQueryModel* trier_nomasc2();
    QSqlQueryModel* trier_nomdesc2();
    QSqlQueryModel* trier_idasc2();
    QSqlQueryModel* trier_iddesc2();
    QSqlQueryModel* trier_nbetageasc2();
    QSqlQueryModel* trier_nbetagedesc2();
    QSqlQueryModel* trier_idbatasc();
    QSqlQueryModel* trier_idbatdesc();
    QSqlQueryModel *rechercherparnom2(const QString &);
    QSqlQueryModel *Find_salle(QString );
   private:
    int idsalle,etage,idbat,nbeleve,fk_classe,fk_employe;
    QString nomsalle,etat;
};

#endif // SALLE_H
