#include "emplois.h"
#include <QDebug>

emplois::emplois()
{

}

emplois::emplois(int id_emplois,QString date_emplois,QString matiere)
{
    this->id_emplois=id_emplois;
    this->date_emplois=date_emplois;
    this->matiere=matiere;
}

int emplois::get_id_emplois(){return  id_emplois;}
QString emplois::get_date_emplois(){return  date_emplois;}
QString emplois::get_matiere(){return  matiere;}

bool emplois::ajouter_em()
{
QSqlQuery query;
QString res= QString::number(id_emplois);
query.prepare("INSERT INTO emplois (ID_EMPLOIS,DATE_EMPLOIS,MATIERE) "
                    "VALUES (:id, :date,:matiere)");
query.bindValue(":id", res);
query.bindValue(":date", date_emplois);
query.bindValue(":matiere",matiere);
return    query.exec();
}

QSqlQueryModel * emplois::afficher_em()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from emplois");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Matière"));

    return model;
}

bool emplois::supprimer_em(int idd)
{
    QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("Delete from emplois where ID_EMPLOIS = :id ");
    query.bindValue(":id", res);
    return    query.exec();
}

bool emplois::modifier_em()
{
    QSqlQuery query;
    QString res= QString::number(id_emplois);
    query.prepare("update emplois set DATE_EMPLOIS=:date_emplois,MATIERE=:matiere where ID_EMPLOIS=:id");
    query.bindValue(":id", res);
    query.bindValue(":date_emplois", date_emplois);
    query.bindValue(":matiere",matiere);
    query.exec();
}

QSqlQueryModel * emplois::chercher_ep(QString numm)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString ref=numm;
    query.prepare("SELECT * from emplois where  id_emplois= :id_emplois");
    query.bindValue(":id_emplois",ref);
query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Vertical, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Vertical, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Vertical, QObject::tr("Matière"));
        return model;
}

QSqlQueryModel * emplois::Find_Emploi(QString id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id_emplois,date_emplois,matiere FROM emplois WHERE id_emplois='"+id+"'");
    query.bindValue(0,id);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *emplois::trier_idAsc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM emplois ORDER BY ID_EMPLOIS ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Matière"));

    return model;
}
QSqlQueryModel *emplois::trier_idDesc2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM emplois ORDER BY ID_EMPLOIS DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Matière"));

    return model;
}



