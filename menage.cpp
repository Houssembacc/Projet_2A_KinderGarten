#include "menage.h"
#include <QDebug>
Menage::Menage()
{
idSalle=0;
nomEmploye="";
typeProduits="";
Duree="";
}

Menage::Menage(int idSalle,QString nomEmploye,QString typeProduits,QString Duree)
{
  this->idSalle=idSalle;
  this->nomEmploye=nomEmploye;
  this->typeProduits=typeProduits;
  this->Duree=Duree;
}

QString Menage::get_nom(){return  nomEmploye;}
QString Menage::get_type(){return  typeProduits;}
QString Menage::get_duree(){return  Duree;}
int Menage::get_idSalle(){return  idSalle;}

bool Menage::ajouter()
{
QSqlQuery query;
QString res= QString::number(idSalle);
query.prepare("INSERT INTO clubs (IDSALLE, DUREE, TYPEPRODUITS, NOMEMPLOYE) "
                    "VALUES (:idSalle, :Duree, :typeProduits, :nomEmploye)");

query.bindValue(":idSalle", res);
query.bindValue(":typeProduits", typeProduits);
query.bindValue(":Duree", Duree);
query.bindValue(":nomEmploye", nomEmploye);

return    query.exec();
}

bool Menage::modifier()
{
    QSqlQuery query;
    QString res= QString::number(idSalle);
    query.prepare("UPDATE menage SET IDSALLE=:idSalle,DUREE=:Duree,TYPEPRODUITS=:typeProduits,NOMEMPLOYE=:nomEmploye WHERE IDSALLE=:idSalle");
    query.bindValue(":idSalle", res);
    query.bindValue(":typeProduits", typeProduits);
    query.bindValue(":nomEmploye", nomEmploye);
    return query.exec();
}

QSqlQueryModel * Menage::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from menage");
model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
    return model;
}

bool Menage::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from menage where IDSALLE = :idSalle ");
query.bindValue(":idSalle", res);
return    query.exec();
}

QSqlQueryModel * Menage::chercher(QString num)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString ref=num;
    query.prepare("SELECT * from menage where  IDSALLE = :idSalle ");
    query.bindValue(":idSalle",ref);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
        return model;

}

QSqlQueryModel * Menage::trier_nomAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM menage ORDER BY NOMEMPLOYE ASC");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
    return model;
}

QSqlQueryModel * Menage::trier_nomDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM menage ORDER BY NOMEMPLOYE DESC");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
    return model;
}

QSqlQueryModel * Menage::trier_idAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM menage ORDER BY IDSALLE ASC");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
    return model;
}

QSqlQueryModel * Menage::trier_idDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM menage ORDER BY IDSALLE DESC");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDSALLE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DUREE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPEPRODUITS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMEMPLOYE"));
    return model;
}

