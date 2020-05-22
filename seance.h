#ifndef SEANCE_H
#define SEANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class seance
{
private:
    int id_seance;
    QString matiere;
    int id_salle;
public:
    seance();
    seance(int,QString,int);
    int get_id();
    int get_idsalle();
    QString get_matiere();
    bool ajouter();
    QSqlQueryModel *  afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* trier_matiereasc();
    QSqlQueryModel* trier_matieredsc();
    QSqlQueryModel* trier_idasc();
    QSqlQueryModel* trier_iddesc();
    QSqlQueryModel *rechercherparmatiere(const QString &);
    QSqlQueryModel *Find_seance(QString );
};

#endif // SEANCE_H
