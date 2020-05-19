#include "batiment.h"
#include <QDebug>
#include <QString>

batiment::batiment()
{
   id=0;
   nbetage=0;
   nom="";
}

batiment::batiment(int id,int nbeta,QString nom)
{
    this->id=id;
    this->nbetage=nbeta;
    this->nom=nom;
}

int batiment::get_id(){return  id;}
int batiment::get_nb(){return  nbetage;}
QString batiment::get_nom(){return  nom;}

bool batiment::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO batiments (ID_BATIMENT,NOM_BATIMENT,NBR_ETAGE)"
                    "VALUES (:id,:nom,:nbetage)");
query.bindValue(":id", res);
query.bindValue(":nbetage",nbetage);
query.bindValue(":nom", nom);
return    query.exec();
}

QSqlQueryModel * batiment::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from batiments");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));



    return model;
}

bool batiment::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from batiments where ID_BATIMENT=:id ");
query.bindValue(":id", res);
return    query.exec();
}
bool batiment::modifier()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("UPDATE batiments SET NOM_BATIMENT=:nom,NBR_ETAGE=:nb where ID_BATIMENT=:id");
query.bindValue(":id", res);
query.bindValue(":nom",nom);
query.bindValue(":nb",nbetage);
return    query.exec();
}
QSqlQueryModel *batiment::trier_nomasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY NOM_BATIMENT ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));

    return model;
}
QSqlQueryModel *batiment::trier_nomdesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY NOM_BATIMENTS DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));

    return model;
}
QSqlQueryModel *batiment::trier_idasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY ID_BATIMENT ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));


    return model;
}
QSqlQueryModel *batiment::trier_iddesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY ID_BATIMENT DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));


    return model;
}
QSqlQueryModel *batiment::trier_nbetageasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY NBR_ETAGE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));


    return model;
}
QSqlQueryModel *batiment::trier_nbetagedesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM batiments ORDER BY NBR_ETAGE DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));


    return model;
}
QSqlQueryModel *batiment::rechercherparnom(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from batiments where (NOM_BATIMENT LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nbetage"));

    return model;
}
QSqlQueryModel * batiment::Find_batiment(QString id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ID_BATIMENT,NOM_BATIMENT,NBR_ETAGE,* FROM batiments WHERE ID_BATIMENT='"+id+"'");
    query.bindValue(0,id);
    query.exec();
    model->setQuery(query);
    return model;
}
