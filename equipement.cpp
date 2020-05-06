#include "equipement.h"
#include <QDebug>
Equipement::Equipement()
{
id=0;
nom="";
}

Equipement::Equipement(int id,QString nom,int quantite,int idSalle,int idClub)
{
  this->id=id;
  this->nom=nom;
  this->quantite=quantite;
  this->idSalle=idSalle;
  this->idClub=idClub;
}

QString Equipement::get_nom(){return  nom;}
int Equipement::get_id(){return  id;}
int Equipement::get_idSalle(){return  idSalle;}
int Equipement::get_idClub(){return  idClub;}
int Equipement::get_quantite(){return  quantite;}

bool Equipement::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
QString res1= QString::number(quantite);
QString res2= QString::number(idSalle);
QString res3= QString::number(idClub);
query.prepare("INSERT INTO equipement (ID, NOM, QUANTITE, IDCLUB, IDSALLE) "
                    "VALUES (:id, :nom, :quantite, :idClub, :idSalle)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":idSalle", res2);
query.bindValue(":idClub", res3);
query.bindValue(":quantite", res1);

return    query.exec();
}

bool Equipement::modifier()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString res1= QString::number(quantite);
    QString res2= QString::number(idSalle);
    QString res3= QString::number(idClub);
    query.prepare("UPDATE equipement SET NOM=:nom,QUANTITE=:quantite,IDCLUB=:idClub,IDSALLE=:idSalle WHERE ID=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":idSalle", res2);
    query.bindValue(":idClub", res3);
    query.bindValue(":quantite", res1);
    return query.exec();
}

QSqlQueryModel * Equipement::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from equipement");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));

    return model;
}

bool Equipement::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from equipement where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

QSqlQueryModel * Equipement::chercher(QString num)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString ref=num;
    query.prepare("SELECT * from equipement where  ID = :id ");
    query.bindValue(":id",ref);
query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
        return model;

}

QSqlQueryModel * Equipement::trier_nomAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement ORDER BY NOM ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
    return model;
}

QSqlQueryModel * Equipement::trier_nomDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement ORDER BY NOM DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
    return model;
}

QSqlQueryModel * Equipement::trier_idAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement ORDER BY ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
    return model;
}

QSqlQueryModel * Equipement::trier_idDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement ORDER BY ID DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IDCLUB"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDSALLE"));
    return model;
}
