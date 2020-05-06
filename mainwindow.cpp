#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QPixmap>
#include "equipement.h"
#include "clubs.h"
#include <QString>
#include <QPdfWriter>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QPixmap pix ("C:/Users/Houccem/Desktop/Kindergarten.png");
    ui->label_pic->setPixmap(pix.scaled(216,233,Qt::KeepAspectRatio));
    ui->tabequipement->setModel(tmpequipement.afficher());
    ui->tabclubs->setModel(tmpclubs.afficher());
    ui->tab_modifier_club->setModel(tmpclubs.afficher());
    ui->tab_modif_batiment->setModel(tmpequipement.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_G_eleves_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_G_clubs_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_modifier_6_clicked()
{
    int id = ui->ID_equipement->text().toInt();
    QString nom= ui->Nom_equipement->text();
    int quantite = ui->quantite->text().toInt();
    int idSalle = ui->ID_salle->text().toInt();
    int idClub = ui->ID_club->text().toInt();
    Equipement e(id,nom,quantite,idClub,idSalle);
    bool test=e.ajouter();
  if(test)
  {
      ui->tabequipement->setModel(tmpequipement.afficher());//refresh
      QMessageBox::information(nullptr, QObject::tr("Ajouter un equipement"),
                  QObject::tr("Equipement ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

  }

}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{
    ui->tabequipement->setModel(tmpequipement.afficher());
}

void MainWindow::on_pushButton_modifier_8_clicked()
{
    int id = ui->comboBox_2->currentText().toInt();
    bool test=tmpequipement.supprimer(id);
    if(test)
    {ui->tabequipement->setModel(tmpequipement.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un equipement"),
                    QObject::tr("Equipement supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
}




void MainWindow::on_pushButton_modifier_2_clicked()
    {
        int id = ui->Id_clubs->text().toInt();
        QString nom= ui->Nom_clubs->text();
        QString type= ui->Type_clubs->text();
        int idSalle = ui->Id_salle->text().toInt();
        int idEmplois = ui->Id_emplois->text().toInt();
        int idEmploye = ui->Id_employe->text().toInt();
        Clubs c(id, nom, type, idSalle, idEmplois, idEmploye);
        bool test=c.ajouter();

      if(test)
      {
          ui->tabclubs->setModel(tmpequipement.afficher());//refresh
          QMessageBox::information(nullptr, QObject::tr("Ajouter un club"),
                      QObject::tr("Club ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }

     }


void MainWindow::on_pb_supprimer_2_clicked()
{

    int id = ui->comboBox_3->currentText().toInt();
    bool test=tmpclubs.supprimer(id);

    if(test)
    {
        ui->tabclubs->setModel(tmpclubs.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un club"),
                    QObject::tr("Club supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->tabclubs->setModel(tmpclubs.afficher());
}

void MainWindow::on_rechercher_ID_salle_textChanged(const QString &arg1)
{
    Clubs c;
            if(arg1!="")
            { ui->tabclubs->setModel(c.chercher(arg1) );}
            if(arg1=="")
            {
                QSqlQueryModel * model=new QSqlQueryModel();
                 ui->tabclubs->setModel(tmpclubs.afficher());
            }
}

void MainWindow::on_rechercher_batiment_textChanged(const QString &arg1)
{
    Equipement e;
            if(arg1!="")
            { ui->tabequipement->setModel(e.chercher(arg1) );}
            if(arg1=="")
            {
                QSqlQueryModel * model=new QSqlQueryModel();
                 ui->tabequipement->setModel(tmpequipement.afficher());
            }
}

void MainWindow::on_pb_trier_salle_clicked()
{
    Clubs c;
          if( ui->comboBox_tri->currentText() == "NOM A-Z") // TRIE par NOMasc
              {ui->tabclubs->setModel(c.trier_nomAsc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par Nom asc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->comboBox_tri->currentText() == "NOM Z-A") // TRIE par NOMdesc
              {ui->tabclubs->setModel(c.trier_nomDesc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par Nom desc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->comboBox_tri->currentText() == "ID ASC") // TRIE par IDasc
          {
              ui->tabclubs->setModel(c.trier_idAsc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par ID asc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->comboBox_tri->currentText() == "ID DESC") // TRIE par IDdesc
          {
              ui->tabclubs->setModel(c.trier_idDesc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par ID desc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_trier_batiment_clicked()
{
    Equipement e;
          if( ui->combo_trier_equipements->currentText() == "NOM A-Z") // TRIE par NOMasc
              {ui->tabequipement->setModel(e.trier_nomAsc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par Nom asc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->combo_trier_equipements->currentText() == "NOM Z-A") // TRIE par NOMdesc
              {ui->tabequipement->setModel(e.trier_nomDesc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par Nom desc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->combo_trier_equipements->currentText() == "ID ASC") // TRIE par IDasc
          {
              ui->tabequipement->setModel(e.trier_idAsc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par ID asc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          if( ui->combo_trier_equipements->currentText() == "ID DESC") // TRIE par IDdesc
          {
              ui->tabequipement->setModel(e.trier_idDesc());
              QMessageBox::information(nullptr, QObject::tr("Trier"),
                                    QObject::tr("Table trie par ID desc.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_pb_modifier_club_clicked()
{
                    int id=ui->ID_modif_club->text().toInt();
                     QString nom=ui->Nom_modif_club->text();
                     QString type=ui->type_modif_club->text();
                     int idSalle=ui->id_modif_salle->text().toInt();
                     int idEmplois=ui->id_modif_emplois->text().toInt();
                     int idEmploye=ui->id_modif_employe->text().toInt();

                   Clubs c(id,nom,type,idSalle,idEmplois,idEmploye); // classe employe pour mettre les champs
                   bool test=c.modifier();
                   if(test)
                   {
                       ui->tab_modifier_club->setModel(tmpclubs.afficher());//refresh
                       QMessageBox::information(nullptr, QObject::tr("Modifier un club"),
                                   QObject::tr("Club modifié.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                   }
                   else
                       QMessageBox::critical(nullptr, QObject::tr("Modifier un club"),
                                   QObject::tr("Erreur !.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_equipement_clicked()
{
     int id=ui->ID_modif_equipement->text().toInt();
     QString nom=ui->Nom_modif_equipement->text();
     int quantite=ui->quantite_modif_equipement->text().toInt();
     int idSalle=ui->idsalle_modif_club->text().toInt();
     int idClub=ui->idclub_modif_club->text().toInt();

   Equipement e(id,nom,quantite,idSalle,idClub); // classe employe pour mettre les champs
   bool test=e.modifier();
   if(test)
   {
       ui->tab_modif_batiment->setModel(tmpequipement.afficher());//refresh
       QMessageBox::information(nullptr, QObject::tr("Modifier un équipement"),
                   QObject::tr("Equipement modifié.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
   }
   else
       QMessageBox::critical(nullptr, QObject::tr("Modifier un équipement"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tabclubs_activated(const QModelIndex &index)
{
    QString val=ui->tabclubs->model()->data(index).toString();
                QSqlQuery q;
                q.prepare("select * from clubs where idClub='"+val+"'");
                if(q.exec())
                {
                    while (q.next())
                    {
                    ui->lineEditPDFF->setText(q.value(0).toString());
                    }
                }
}



void MainWindow::on_clickPDF_clicked()
{
    QPdfWriter pdf("C:/Users/user16/Desktop/clubs.pdf");
            QPainter painter;
            if (! painter.begin(&pdf))
            {
                // failed to open file
                                qWarning("failed to open file, is it writable?");

            }
            QString id =ui->lineEditPDFF->text();
            const time_t ctt = time(0);
            QSqlQuery query;
            query.exec("SELECT ID, IDSALLE, IDEMPLOYE, TYPE, IDEMPLOIS, NOM FROM clubs WHERE ID='"+id+"'");

                    while (query.next())
                          {

                        QString id = query.value(0).toString();
                        QString idSalle = query.value(1).toString();
                        QString idEmploye = query.value(2).toString();
                        QString type = query.value(3).toString();
                        QString idEmplois = query.value(4).toString();
                        QString nom = query.value(5).toString();


                painter.drawText(2200,3500,id);
                painter.drawText(2200,4000,idSalle);
                painter.drawText(2200,4500,idEmploye);
                painter.drawText(2200,5000,type);
                painter.drawText(2200,5500,idEmplois);
                painter.drawText(2200,6000,nom);


                painter.setPen(Qt::blue);
                painter.setPen(Qt::black);
                painter.drawText(500,2000,asctime(localtime(&ctt)));
                painter.drawText(500,3500,"Identifiant:");
                painter.drawText(500,4000,"Id salle :");
                painter.drawText(500,4500,"Id employé :");
                painter.drawText(500,5000,"Type :");
                painter.drawText(500,5500,"Id emplois :");
                painter.drawText(500,6000,"Nom :");

            }
                     QMessageBox::information (this,"PDF","Export fait avec succès!");
}

void MainWindow::on_tabequipement_activated(const QModelIndex &index)
{
    QString val=ui->tabequipement->model()->data(index).toString();
                QSqlQuery q;
                q.prepare("select * from equipement where id='"+val+"'");
                if(q.exec())
                {
                    while (q.next())
                    {
                    ui->lineEditEquipement->setText(q.value(0).toString());
                    }
                }
}

void MainWindow::on_clickPDF_2_clicked()
{
    QPdfWriter pdf("C:/Users/user16/Desktop/equipement.pdf");
            QPainter painter;
            if (! painter.begin(&pdf))
            {
                // failed to open file
                                qWarning("failed to open file, is it writable?");

            }
            QString id =ui->lineEditEquipement->text();
            const time_t ctt = time(0);
            QSqlQuery query;
            query.exec("SELECT ID, NOM, QUANTITE, IDCLUB, IDSALLE FROM equipement WHERE ID='"+id+"'");

                    while (query.next())
                          {

                        QString id = query.value(0).toString();
                        QString nom = query.value(1).toString();
                        QString idSalle = query.value(2).toString();
                        QString idClub = query.value(3).toString();
                        QString quantite = query.value(4).toString();

                painter.drawText(2200,3500,id);
                painter.drawText(2200,4000,nom);
                painter.drawText(2200,4500,idSalle);
                painter.drawText(2200,5000,idClub);
                painter.drawText(2200,5500,quantite);


                painter.setPen(Qt::blue);
                painter.setPen(Qt::black);
                painter.drawText(500,2000,asctime(localtime(&ctt)));
                painter.drawText(500,3500,"Identifiant:");
                painter.drawText(500,4000,"Nom :");
                painter.drawText(500,4500,"Id Salle :");
                painter.drawText(500,5000,"Id club :");
                painter.drawText(500,5500,"Quantite :");

            }
                     QMessageBox::information (this,"PDF","Export fait avec succès!");
}

void MainWindow::on_tab_modifier_club_activated(const QModelIndex &index)
{
    QString val=ui->tab_modifier_club->model()->data(index).toString();
              QSqlQuery q;
              q.prepare("select * from clubs where ID='"+val+"'");
              if(q.exec())
              {
                  while (q.next())
                  {
                  ui->ID_modif_club->setText(q.value(0).toString());
                  ui->Nom_modif_club->setText(q.value(1).toString());
                  ui->type_modif_club->setText(q.value(2).toString());
                  ui->id_modif_salle->setText(q.value(3).toString());
                  ui->id_modif_emplois->setText(q.value(4).toString());
                  ui->id_modif_employe->setText(q.value(5).toString());
                  }
              }
}

void MainWindow::on_tab_modif_batiment_activated(const QModelIndex &index)
{
    QString val=ui->tab_modif_batiment->model()->data(index).toString();
              QSqlQuery q;
              q.prepare("select * from equipement where ID='"+val+"'");
              if(q.exec())
              {
                  while (q.next())
                  {
                  ui->ID_modif_equipement->setText(q.value(0).toString());
                  ui->Nom_modif_equipement->setText(q.value(1).toString());
                  ui->quantite_modif_equipement->setText(q.value(2).toString());
                  ui->idsalle_modif_club->setText(q.value(3).toString());
                  ui->idclub_modif_club->setText(q.value(4).toString());
                  }
              }
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    QSqlQueryModel *modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID from equipement");
        q.exec();
        modal->setQuery(q);
        ui->comboBox_2->setModel(modal);
}

void MainWindow::on_stat_2_currentChanged(int index)
{
    QSqlQueryModel *modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID from clubs");
        q.exec();
        modal->setQuery(q);
        ui->comboBox_3->setModel(modal);
}
