#include "food.h"

food::food()
{
    entree="";
    principale="";
    dessert="";
    jour="";
    id=0;
}

food::food(QString entree,QString principale,QString dessert,QString jour,int id) // constructeur parametré
{
    this->entree=entree;
    this->principale=principale;
    this->dessert=dessert;
    this->jour=jour;
    this->id=id;
}

QString food::get_entree(){return entree;}

QString food::get_principale(){return principale;}

QString food::get_dessert(){return dessert;}
QString food::get_jour(){return jour;}
int food::get_id(){return id;}

bool food::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO MENU (ENTRÉE,PLAT_PRINCIPALE,DESSERT,Jour,ID) "
                    "VALUES (:entree, :principale, :dessert, :jour, :id)");

query.bindValue(":entree", entree);
query.bindValue(":principale", principale);
query.bindValue(":dessert", dessert);
query.bindValue(":jour", jour);
query.bindValue(":id", res);
return    query.exec();
}

bool food::supprimer(QString jour)
{
QSqlQuery query;
//QString res= QString::number(id);
query.prepare("Delete from MENU where Jour = :jour "); // supprimer selon le jour ...
query.bindValue(":jour", jour);
return    query.exec();
}

bool food::update()
{
    food f;
    QString id=QString::number(this->id);
    QSqlQuery query;
    if(entree != "")
    {
        query.prepare("update  MENU set ENTRÉE ='"+entree+"'where ID ='"+id+"'");
        query.exec();
    }

    if (principale!="")
    {
        query.prepare("update  MENU set PLAT_PRINCIPALE ='"+principale+"'where ID ='"+id+"'");
        query.exec();
    }
    if(dessert!="")
    {
        query.prepare("update  MENU set DESSERT ='"+dessert+"'where ID ='"+id+"'");
        query.exec();
    }

    if(jour!="")
    {
        query.prepare("update  MENU set Jour ='"+jour+"'where ID ='"+id+"'");
        query.exec();
    }
    return query.exec();
}

QSqlQueryModel * food::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from MENU");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ENTRÉE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESSERT"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
    return model;
}

QSqlQueryModel * food::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY ID ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel * food::trier_plat()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY PLAT_PRINCIPALE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel * food::trier_jour()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY Jour ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

    return model;
}
