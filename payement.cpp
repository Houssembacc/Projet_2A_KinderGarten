#include "payement.h"

Payement::Payement()
{
    id=0;
    id_eleve_fk=0;
    type="";
    date="";
    prix=0;
}

Payement::Payement(int id,int id_eleve_fk,int prix,QString type,QString date )
{
  this->id=id;
   this->id_eleve_fk=id_eleve_fk;
  this->prix=prix;
  this->date=date;
  this->type=type;

}
int Payement::get_id(){return  id;}
int Payement::get_ideleve(){return id_eleve_fk;}
QString Payement::get_type(){return  type;}
int Payement::get_prix(){return  prix;}
QString Payement::get_date(){return date;}


bool Payement::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO PAYEMENT (ID,ID_ELEVE_FK,PRIX,TYPE,DATE_PAYEMENT) "
                    "VALUES (:id, :idel, :prix, :type, :date)");
query.bindValue(":id", res);
query.bindValue(":idel", id_eleve_fk);
query.bindValue(":prix", prix);
query.bindValue(":type", type);
query.bindValue(":date", date);


return    query.exec();
}

QSqlQueryModel * Payement::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PAYEMENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_ELEVE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE DE PAYEMENT"));

    return model;
}

bool Payement::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from PAYEMENT where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Payement:: update()
{
    QSqlQuery query;
    int first=0 ;
        QString res1=QString::number(id);
         QString editer="Update PAYEMENT set" ;

        query.bindValue(":type",type);
        if(type!="")
        {
            editer+=" TYPE = :type" ;
            first=1 ;
        }
        query.bindValue(":date",date);
        if(date!=""&& first!=0)
            editer+=" ,DATE_PAYEMENT= :date" ;
        else if (date!=""&&first==0)
          {
            editer+=" DATE_PAYEMENT= :date" ;
            first=1 ;
          }
        query.bindValue(":idel",id_eleve_fk);
        if(id_eleve_fk!=NULL && first!=0)
            editer+=" ,ID_ELEVE_FK = :idel" ;
        else if (id_eleve_fk!=NULL && first==0)
        {
           editer+=" ID_ELEVE_FK= :idel" ;
           first=1 ;
        }

        query.bindValue(":prix",prix);
        if(prix!=NULL && first!=0)
            editer+=" ,PRIX = :prix" ;
        else if (prix!=NULL && first==0)
        {
           editer+=" ID_ELEVE_FK= :prix" ;
           first=1 ;
        }
               editer+=" where ID = :id" ;



               QByteArray chaine = editer.toLocal8Bit();
               const char *final = chaine.data();



            query.prepare(final);

               //query.prepare("Update BUS set MODELE= :modele,ETAT = :etat,DATE_ACHAT = :date_achat  where ID = :id");

         query.bindValue(":id",QVariant(res1).toInt());
         query.bindValue(":id", res1);
         query.bindValue(":idel", id_eleve_fk);
         query.bindValue(":prix", prix);
         query.bindValue(":type", type);
         query.bindValue(":date", date);

         return query.exec();
}
QSqlQueryModel *Payement::recherchernom(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PAYEMENT where (ID LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID ELEVE "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE"));

    return model;
}
