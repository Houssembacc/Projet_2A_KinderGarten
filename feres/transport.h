#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class TRANSPORT
{
public:
    TRANSPORT();
    TRANSPORT(QString,QString,int,int); // constructeur parametré
    QString get_matricule();
    QString get_trajet();
    int get_places();
    int get_inscrit();
    bool ajouter(); // ajouter
    QSqlQueryModel * afficher(); // afficher
    bool supprimer(QString); // supprimer
    bool update();
private:
    QString matricule,trajet;
    int places,inscrit;
};

#endif // TRANSPORT_H
