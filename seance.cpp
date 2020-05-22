#include "seance.h"
#include <QtDebug>
seance::seance()
{
   id_seance=0;
  matiere="";
  id_salle=0;
}

seance::seance(int idseance,QString matiere,int idsalle )
{
    this->id_seance=idseance;
    this->matiere=matiere;
    this->id_salle=idsalle;
}

int seance::get_idsalle(){return  id_salle;}
int seance::get_id(){return  id_seance;}
QString seance::get_matiere(){return  matiere;}


bool seance::ajouter()
{
QSqlQuery query;
QString res= QString::number(id_seance);
query.prepare("INSERT INTO SEANCES (ID_SEANCE,MATIERE,ID_SALLE) "
                    "VALUES (:idseance,:matiere,:idsalle)");
query.bindValue(":idseance", res);
query.bindValue(":matiere", matiere);
query.bindValue(":idsalle",id_salle);
return    query.exec();
}

QSqlQueryModel * seance::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select ID_SEANCE,MATIERE,ID_SALLE from SEANCES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matiere "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_Salle"));

    return model;
}
bool seance::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from SEANCES where ID_SEANCE=:id ");
query.bindValue(":id", res);
return    query.exec();
}
bool seance::modifier()
{
QSqlQuery query;
QString res= QString::number(id_seance);
query.prepare("UPDATE SEANCES SET MATIERE=:mt,ID_SALLE=:idsalle where ID_SEANCE=:idseance");
query.bindValue(":idseance", res);
query.bindValue(":mt",matiere);
query.bindValue(":idsalle",id_salle);
return    query.exec();
}

QSqlQueryModel *seance::trier_matiereasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SEANCES ORDER BY MATIERE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_SALLE"));
    return model;
}
QSqlQueryModel *seance::trier_matieredsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SEANCES ORDER BY MATIERE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_SALLE"));
    return model;
}
QSqlQueryModel *seance::trier_idasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SEANCES ORDER BY ID_SEANCE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_SALLE"));
    return model;
}
QSqlQueryModel *seance::trier_iddesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SEANCES ORDER BY ID_SEANCE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Matière"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_SALLE"));
    return model;
}
QSqlQueryModel *seance::rechercherparmatiere(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from SEANCES where (MATIERE LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("etage"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_bat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("état"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nb élève"));
    return model;


}
QSqlQueryModel *seance::Find_seance(QString id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT  ID_SEANCE,MATIERE,ID_SALLE FROM seances WHERE ID_SEANCE='"+id+"'");
    query.bindValue(0,id);
    query.exec();
    model->setQuery(query);
    return model;
}
