#include "employe.h"
#include <QDebug>


employe::employe()
{

}

employe::employe(int id_employe,QString nom_employe,QString prenom_employe,QString sexe,QString date_naissance_employe,int cin_employe,QString adresse_employez)
{
    this->id_employe=id_employe;
    this->nom_employe=nom_employe;
    this->prenom_employe=prenom_employe;
    this->sexe=sexe;
    this->date_naissance_employe=date_naissance_employe;
    this->cin_employe=cin_employe;
    this->adresse_employe=adresse_employe;
}

int employe::get_id(){return  id_employe;}
QString employe::get_nom(){return  nom_employe;}
QString employe::get_prenom(){return  prenom_employe;}
QString employe::get_sexe(){return  sexe;}
QString employe::get_date_naissance(){return  date_naissance_employe;}
int employe::get_cin(){return  cin_employe;}
QString employe::get_adresse(){return  adresse_employe;}


bool employe::ajouter()
{
QSqlQuery query;
QString res= QString::number(id_employe);
query.prepare("INSERT INTO employe (ID_EMPLOYE, NOM_EMPLOYE, PRENOM_EMPLOYE,SEXE,DATE_NAISSANCE_EMPLOYE,CIN_EMPLOYE,ADRESSE_EMPLOYE) "
                    "VALUES (:id, :nom, :prenom, :sexe, :date_naissance, :cin, :adresse)");
query.bindValue(":id", res);
query.bindValue(":nom", nom_employe);
query.bindValue(":prenom", prenom_employe);
query.bindValue(":sexe", sexe);
query.bindValue(":date_naissance", date_naissance_employe);
query.bindValue(":cin", cin_employe);
query.bindValue(":adresse", adresse_employe);


return    query.exec();
}

QSqlQueryModel * employe::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from employe");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));

    return model;
}

bool employe::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from employe where ID_EMPLOYE = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool employe::modifier()
{
    QSqlQuery query;
    QString res= QString::number(id_employe);
    query.prepare("update employe set NOM_EMPLOYE=:nom,PRENOM_EMPLOYE=:prenom,DATE_NAISSANCE_EMPLOYE=:date_naissance,CIN_EMPLOYE=:cin where ID_EMPLOYE=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom_employe);
    query.bindValue(":prenom", prenom_employe);
    query.bindValue(":date_naissance", date_naissance_employe);
    query.bindValue(":cin", cin_employe);
    query.exec();
}

QSqlQueryModel * employe::chercher(QString num)
{QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    QString ref=num;
    query.prepare("SELECT * from employe where  id_employe= :id_employe");
    query.bindValue(":id_employe",ref);
query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Vertical, QObject::tr("id_employe"));
    model->setHeaderData(1, Qt::Vertical, QObject::tr("nom_employe"));
    model->setHeaderData(2, Qt::Vertical, QObject::tr("prenom_employe "));
    model->setHeaderData(3, Qt::Vertical, QObject::tr("sexe"));
    model->setHeaderData(4, Qt::Vertical, QObject::tr("date_naissance_employe"));
    model->setHeaderData(5, Qt::Vertical, QObject::tr("cin_employe"));
    model->setHeaderData(6, Qt::Vertical, QObject::tr("adresse_employe"));
        return model;

}
QSqlQueryModel * employe::Find_Employe(QString id)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id_employe,nom_employe,prenom_employe,sexe,date_naissance_employe,cin_employe,adresse_employe FROM employe WHERE id_employe='"+id+"'");
    query.bindValue(0,id);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel *employe::trier_nomAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY NOM_EMPLOYE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}
QSqlQueryModel *employe::trier_nomDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY NOM_EMPLOYE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}
QSqlQueryModel *employe::trier_idAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY ID_EMPLOYE ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}
QSqlQueryModel *employe::trier_idDesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY ID_EMPLOYE DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}
