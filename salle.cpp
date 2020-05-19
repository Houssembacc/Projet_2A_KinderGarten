#include "salle.h"
#include <QDebug>
#include <QString>
#include "batiment.h"
salle::salle()
{
   idsalle=0;
   etage=0;
   nomsalle="";
   idbat=0;
}

salle::salle(int idsalle,QString nom,int eta,int fk_classe,int fk_employe,int idbat,QString etat,int nb)
{
    this->idsalle=idsalle;
    this->etage=eta;
    this->nomsalle=nom;
    this->idbat=idbat;
    this->etat=etat;
    this->fk_classe=fk_classe;
    this->fk_employe=fk_employe;
    this->nbeleve=nb;
}

int salle::get_idsalle(){return  idsalle;}
int salle::get_etage(){return  etage;}
QString salle::get_nomsalle(){return  nomsalle;}
int salle::get_idbat(){return idbat;}
QString salle::get_etat(){return etat;}
int salle::get_nbeleve(){return nbeleve;}

bool salle::ajoutersalle()
{
QSqlQuery query;
QString res= QString::number(idsalle);
query.prepare("INSERT INTO SALLES (ID_SALLE,NOM_SALLE,NUM_ETAGE,REF_CLASSE_FK,ID_EMPLOYE_FK,ID_BATIMENT_FK,ETAT,NBELEVE) "
                    "VALUES (:idsalle,:nom,:eta,:classe,:employe,:idbat,:etat,:nb)");
query.bindValue(":idsalle", res);
query.bindValue(":nom", nomsalle);
query.bindValue(":eta",etage);
query.bindValue(":classe",fk_classe);
query.bindValue(":employe",fk_employe);
query.bindValue(":idbat",idbat);
query.bindValue(":etat",etat);
query.bindValue(":nb",nbeleve);


return    query.exec();
}

QSqlQueryModel * salle::affichersalle()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select ID_SALLE,NOM_SALLE,NUM_ETAGE,REF_CLASSE_FK,ID_EMPLOYE_FK,ID_BATIMENT_FK,ETAT,NBELEVE from SALLES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etage"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Classe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Employe"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_bat"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("état"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("nb élève"));

    return model;
}
bool salle::supprimersalle(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from SALLES where ID_SALLE=:id ");
query.bindValue(":id", res);
return    query.exec();
}
bool salle::modifier()
{
QSqlQuery query;
QString res= QString::number(idsalle);
query.prepare("UPDATE SALLES SET NOM_SALLE=:nom,NUM_ETAGE=:etage,ID_BATIMENT_FK=:idb,ETAT=:et,NBELEVE=:nb where ID_SALLE=:ids");
query.bindValue(":ids", res);
query.bindValue(":etage",etage);
query.bindValue(":nom",nomsalle);
query.bindValue(":idb",idbat);
query.bindValue(":et",etat);
query.bindValue(":nb",nbeleve);

return    query.exec();
}
QSqlQueryModel *salle::trier_nomasc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY NOM_SALLE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::trier_nomdesc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY NOM_SALLE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::trier_idasc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY ID_SALLE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));

    return model;
}
QSqlQueryModel *salle::trier_iddesc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY ID_SALLE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));

    return model;
}
QSqlQueryModel *salle::trier_nbetageasc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY NUM_ETAGE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::trier_nbetagedesc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY NUM_ETAGE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::trier_idbatasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY ID_BATIMENT_FK ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::trier_idbatdesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SALLES ORDER BY ID_BATIMENT_FK DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;
}
QSqlQueryModel *salle::rechercherparnom2(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from SALLES where (NOM_SALLE LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;


}
QSqlQueryModel *salle::Find_salle(QString id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT  ID_SALLE,NOM_SALLE,NUM_ETAGE,REF_CLASSE_FK,ID_EMPLOYE_FK,ID_BATIMENT_FK,ETAT,NBELEVE FROM salles WHERE ID_SALLE='"+id+"'");
    query.bindValue(0,id);
    query.exec();
    model->setQuery(query);
    return model;
}
