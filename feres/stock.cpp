#include "stock.h"

stock::stock()
{
    id="";
    nom="";
    type="";
    qte=0;
    //lim="00/00/0000";
}


stock::stock(QString id,QString nom,QString type,int qte) // constructeur parametré
{
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->qte=qte;
    //this->lim=lim;
}

QString stock::get_id(){return id;}
QString stock::get_nom(){return nom;}
QString stock::get_type(){return type;}
int stock::get_qte(){return qte;}
//QDate stock::get_lim(){return lim;}

bool stock::ajouter()
{
QSqlQuery query;
QString res= QString::number(qte);
query.prepare("INSERT INTO STOCK (ID,NOM,QUANTITE,TYPE) "
                    "VALUES (:id, :nom, :qte, :type)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":qte", res);
query.bindValue(":type", type);

return    query.exec();
}

QSqlQueryModel * stock::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from STOCK");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    return model;
}

bool stock::supprimer(QString id)
{
QSqlQuery query;
//QString res= QString::number(id);
query.prepare("Delete from STOCK where ID = :id "); // supprimer selon le jour ...
query.bindValue(":id", id);
return    query.exec();
}

bool stock::update()
{
    stock s;
    QString qte=QString::number(this->qte);
    QSqlQuery query;
    if(nom != "")
        {
            query.prepare("update  STOCK set NOM ='"+nom+"'where ID ='"+id+"'");
            query.exec();
        }

    if(qte != "")
        {
            query.prepare("update  STOCK set QUANTITE ='"+qte+"'where ID ='"+id+"'");
            query.exec();
        }

    if(type != "")
        {
            query.prepare("update  STOCK set TYPE ='"+type+"'where ID ='"+id+"'");
            query.exec();
        }

    return query.exec();
}




