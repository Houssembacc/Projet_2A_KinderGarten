#include "clubs.h"
#include <QDebug>
Clubs::Clubs()
{
id=0;
nom="";
type="";
idSalle=0;
idEmplois=0;
idEmploye=0;
}

Clubs::Clubs(int id,QString nom,QString type,int idSalle,int idEmplois,int idEmploye)
{
  this->id=id;
  this->nom=nom;
  this->type=type;
  this->idSalle=idSalle;
  this->idEmplois=idEmplois;
  this->idEmploye=idEmploye;
}

QString Clubs::get_nom(){return  nom;}
QString Clubs::get_type(){return  type;}
int Clubs::get_id(){return  id;}
int Clubs::get_idSalle(){return  idSalle;}
int Clubs::get_idEmplois(){return  idEmplois;}
int Clubs::get_idEmploye(){return  idEmploye;}

bool Clubs::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
QString res1= QString::number(idSalle);
QString res2= QString::number(idEmplois);
QString res3= QString::number(idEmploye);
query.prepare("INSERT INTO clubs (ID, IDSALLE, IDEMPLOYE, TYPE, IDEMPLOIS, NOM) "
                    "VALUES (:id, :idSalle, :idEmploye, :type, :idEmplois, :nom)");
query.bindValue(":id", res);
query.bindValue(":idSalle", res1);
query.bindValue(":idEmploye", res3);
query.bindValue(":type", type);
query.bindValue(":idEmplois", res2);
query.bindValue(":nom", nom);

return    query.exec();
}

bool Clubs::modifier()
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString res1= QString::number(idSalle);
    QString res2= QString::number(idEmplois);
    QString res3= QString::number(idEmploye);
    query.prepare("UPDATE clubs SET IDSALLE=:idSalle,IDEMPLOYE=:idEmploye,TYPE=:type,IDEMPLOIS=:idEmplois,NOM=:nom WHERE ID=:id");
    query.bindValue(":id", res);
    query.bindValue(":idSalle", res1);
    query.bindValue(":idEmploye", res3);
    query.bindValue(":type", type);
    query.bindValue(":idEmplois", res2);
    query.bindValue(":nom", nom);
    return query.exec();
}

QSqlQueryModel * Clubs::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from clubs");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
    return model;
}

bool Clubs::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from clubs where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

QSqlQueryModel * Clubs::chercher(QString num)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString ref=num;
    query.prepare("SELECT * from clubs where  ID = :id ");
    query.bindValue(":id",ref);
query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
        return model;

}

QSqlQueryModel * Clubs::trier_nomAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM clubs ORDER BY NOM ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
    return model;
}

QSqlQueryModel * Clubs::trier_nomDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM clubs ORDER BY NOM DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
    return model;
}

QSqlQueryModel * Clubs::trier_idAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM clubs ORDER BY ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
    return model;
}

QSqlQueryModel * Clubs::trier_idDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM clubs ORDER BY ID DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDEMPLOYE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("IDEMPLOIS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM "));
    return model;
}

