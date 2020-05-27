#include "transport.h"

TRANSPORT::TRANSPORT()
{
    matricule="";
    trajet="";
    places=0;
    inscrit=0;

}

TRANSPORT::TRANSPORT(QString matricule,QString trajet,int places,int inscrit)
{
    this->matricule=matricule;
    this->trajet=trajet;
    this->places=places;
    this->inscrit=inscrit;
}
QString TRANSPORT::get_matricule(){return matricule;}

QString TRANSPORT::get_trajet(){return trajet;}

int TRANSPORT::get_places(){return places;}

int TRANSPORT::get_inscrit(){return inscrit;}

bool TRANSPORT::ajouter()
{
QSqlQuery query;
QString res= QString::number(places);
QString res2= QString::number(inscrit);
query.prepare("INSERT INTO TRANSPORT (MATRICULE,TRAJET,NBR_PLACES,NBR_INSCRIT) "
                    "VALUES (:matricule, :trajet, :nbr_places, :nbr_inscrit)");
query.bindValue(":matricule", matricule);
query.bindValue(":trajet", trajet);
query.bindValue(":nbr_places", res);
query.bindValue(":nbr_inscrit", res2);

return    query.exec();
}

QSqlQueryModel * TRANSPORT::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from TRANSPORT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("TRAJET"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR_PLACES"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NBR_INSCRIT"));
    return model;
}

bool TRANSPORT::supprimer(QString matricule)
{
    QSqlQuery query;
    query.prepare("Delete from TRANSPORT where MATRICULE = :matricule ");
    query.bindValue(":matricule", matricule);
    return    query.exec();
}

bool TRANSPORT::update()
{
    TRANSPORT t;
    QString places=QString::number(this->places);
    QString inscrit=QString::number(this->inscrit);
    QSqlQuery query;
    if(trajet != "")
        {
            query.prepare("update  TRANSPORT set TRAJET ='"+trajet+"'where MATRICULE ='"+matricule+"'");
            query.exec();
        }

    if(places != "")
        {
            query.prepare("update  TRANSPORT set NBR_PLACES ='"+places+"'where MATRICULE ='"+matricule+"'");
            query.exec();
        }

    if(inscrit != "")
        {
            query.prepare("update  TRANSPORT set NBR_INSCRIT ='"+inscrit+"'where MATRICULE ='"+matricule+"'");
            query.exec();
        }

    return query.exec();
}
