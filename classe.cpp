#include "classe.h"
#include <QDebug>
classe::classe()
{
    ref=0;
    type="";
}
classe::classe(int ref,QString type)
{
  this->ref=ref;
  this->type=type;
}
QString classe::get_type(){return  type;}

int classe::get_ref(){return  ref;}
bool classe::ajouter_classe()
{
QSqlQuery query;
QString res= QString::number(ref);
query.prepare("INSERT INTO CLASSES  (REFERENCE,TYPE) "
                    "VALUES (:ref, :type)");
query.bindValue(":ref", ref);
query.bindValue(":type", type);

return    query.exec();
}
QSqlQueryModel * classe::afficher_classe()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLASSES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE "));

    return model;
}

bool classe::supprimer_classe(int reff)
{
QSqlQuery query;
QString res= QString::number(reff);
query.prepare("Delete from CLASSES where REFERENCE = :ref "); // supprimer selon un identifiant donné ...
query.bindValue(":ref", res);
return    query.exec();
}

bool classe:: update_classe()
{
    QSqlQuery query;
    int first=0 ;
        QString res1=QString::number(ref);
         QString editer="Update CLASSES set" ;


        query.bindValue(":type",type);
        if(type!=""&& first!=0)
            editer+=" ,TYPE= :type" ;
        else if (type!=""&&first==0)
          {
            editer+=" TYPE= :type" ;
            first=1 ;
          }


               editer+=" where REFERENCE = :ref" ;



               QByteArray chaine = editer.toLocal8Bit();
               const char *final = chaine.data();

             /*  QMessageBox::information(nullptr, QObject::tr("Supprimer un employé"),
                           QObject::tr(final
                                       ), QMessageBox::Cancel); */

            query.prepare(final);

               //query.prepare("Update BUS set MODELE= :modele,ETAT = :etat,DATE_ACHAT = :date_achat  where ID = :id");

         query.bindValue(":ref",QVariant(res1).toInt());
         query.bindValue(":ref", res1);
         query.bindValue(":type", type);


         return query.exec();
}
QSqlQueryModel * classe::trier_type()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLASSES ORDER BY TYPE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID emplois"));


    return model;
}
QSqlQueryModel * classe::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLASSES ORDER BY REFERENCE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID emplois"));


    return model;
}
QSqlQueryModel *classe::recherchertype(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CLASSES where (TYPE LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr(""));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID emplois "));

    return model;


}
