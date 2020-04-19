#include "food.h"

food::food()
{
    id=0;
    entree="";
    principale="";
    dessert="";
    jour="";
}

food::food(int id,QString entree,QString principale,QString dessert,QString jour) // constructeur parametré
{
    this->id=id;
    this->entree=entree;
    this->principale=principale;
    this->dessert=dessert;
    this->jour=jour;
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
query.prepare("INSERT INTO MENU (ID,ENTRÉE,PLAT_PRINCIPALE,DESSERT,Jour) "
                    "VALUES ( :id,:entree, :principale, :dessert, :jour)");

query.bindValue(":id", res);
query.bindValue(":entree", entree);
query.bindValue(":principale", principale);
query.bindValue(":dessert", dessert);
query.bindValue(":jour", jour);
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
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ENTRÉE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESSERT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Jour"));
    return model;
}

QSqlQueryModel * food::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY ID ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Jour"));

    return model;
}

QSqlQueryModel * food::trier_plat()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY PLAT_PRINCIPALE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Jour"));

    return model;
}

QSqlQueryModel * food::trier_jour()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM MENU ORDER BY Jour ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Jour"));

    return model;
}

QSqlQueryModel *food::chercher(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from MENU where JOUR LIKE '"+c+"%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ENTRÉE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PLAT_PRINCIPALE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESSERT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Jour"));
    return model;
}
