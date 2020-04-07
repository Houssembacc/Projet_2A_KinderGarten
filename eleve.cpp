#include "eleve.h"
#include <QDebug>
Eleve::Eleve()
{
    id=0;
    reference=0;
    nom="";
    prenom="";
    adresse="";
    datenaissance="";
    sexe="";
}
Eleve::Eleve(int id,QString nom,QString prenom,QString adresse,QString datenaissance,QString sexe,int reference)
{
  this->id=id;
    this->reference=reference;
  this->nom=nom;
  this->prenom=prenom;
  this->adresse=adresse;
  this->datenaissance=datenaissance;
  this->sexe=sexe;

}
QString Eleve::get_nom(){return  nom;}
QString Eleve::get_prenom(){return prenom;}
int Eleve::get_id(){return  id;}
int Eleve::get_reference(){return  reference;}
QString Eleve::get_adresse(){return adresse;}
QString Eleve::get_date_naissance(){return datenaissance;}

bool Eleve::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO TABLE1 (ID,NOM,PRENOM,ADRESSE,DATENAISSANCE,SEXE,REF_CLASSE_FK) "
                    "VALUES (:id, :nom, :prenom, :adresse, :datenaissance, :sexe, :reference)");
query.bindValue(":id", res);
query.bindValue(":reference", reference);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":adresse", adresse);
query.bindValue(":datenaissance", datenaissance);
query.bindValue(":sexe", sexe);

return    query.exec();
}
QSqlQueryModel * Eleve::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from TABLE1");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));
    return model;
}

bool Eleve::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from TABLE1 where ID = :id "); // supprimer selon un identifiant donné ...
query.bindValue(":id", res);
return    query.exec();
}

bool Eleve:: update()
{
    QSqlQuery query;
    int first=0 ;
        QString res1=QString::number(id);
         QString editer="Update TABLE1 set" ;

        query.bindValue(":nom",nom);
        if(nom!="")
        {
            editer+=" NOM = :nom" ;
            first=1 ;
        }
        query.bindValue(":prenom",prenom);
        if(prenom!=""&& first!=0)
            editer+=" ,PRENOM= :prenom" ;
        else if (prenom!=""&&first==0)
          {
            editer+=" PRENOM= :prenom" ;
            first=1 ;
          }
             query.bindValue(":adresse",adresse);
             if(adresse!=""&& first!=0)
                 editer+=" ,ADRESSE = :adresse" ;
             else if (adresse!="" && first==0)
             {
                editer+=" ADRESSE= :adresse" ;
                first=1 ;
             }
             query.bindValue(":sexe",sexe);
             if(sexe!=""&& first!=0)
                 editer+=" ,SEXE = :sexe" ;
             else if (sexe!="" && first==0)
             {
                editer+=" SEXE= :sexe" ;
                first=1 ;
             }
             query.bindValue(":datenaissance",datenaissance);
             if(datenaissance!=""&& first!=0)
                 editer+=" ,DATENAISSANCE = :datenaissance" ;
             else if (datenaissance!="" && first==0)
             {
                editer+=" DATENAISSANCE= :datenaissance" ;
                first=1 ;
             }
             query.bindValue(":reference",reference);
             if(reference!=NULL && first!=0)
                 editer+=" ,REF_CLASSE_FK = :reference" ;
             else if (reference!=NULL && first==0)
             {
                editer+=" REF_CLASSE_FK= :reference" ;
                first=1 ;
             }
               editer+=" where ID = :id" ;



               QByteArray chaine = editer.toLocal8Bit();
               const char *final = chaine.data();

             /*  QMessageBox::information(nullptr, QObject::tr("Supprimer un employé"),
                           QObject::tr(final
                                       ), QMessageBox::Cancel); */

            query.prepare(final);

               //query.prepare("Update BUS set MODELE= :modele,ETAT = :etat,DATE_ACHAT = :date_achat  where ID = :id");

         query.bindValue(":id",QVariant(res1).toInt());
         query.bindValue(":id", res1);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":adresse", adresse);
         query.bindValue(":sexe", sexe);
         query.bindValue(":datenaissance", datenaissance);
         query.bindValue(":reference", reference);

         return query.exec();
}
QSqlQueryModel * Eleve::trier_id_eleve_asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY ID asc");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));

    return model;
}
QSqlQueryModel * Eleve::trier_id_eleve_desc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY ID desc");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));

    return model;
}
QSqlQueryModel * Eleve::trier_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY NOM ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));

    return model;
}
QSqlQueryModel * Eleve::trier_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY PRENOM ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));

    return model;
}
QSqlQueryModel *Eleve::recherchernom(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from TABLE1 where (NOM LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datenaissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Reference du classe"));
    return model;


}
