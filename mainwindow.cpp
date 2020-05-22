#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_stat_eleve.h"
#include "statistique.h"
#include "ui_statistique.h"
#include "stat_eleve.h"
#include <QPrintDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "eleve.h"
#include "classe.h"
#include "salle.h"
#include "batiment.h"
#include "emploi.h"
#include "employe.h"
#include "equipement.h"
#include "clubs.h"
#include <QPixmap>
#include <QMediaPlayer>
#include "SMTPClient/smtpclient.h"
#include <QDesktopServices>
#include <donutbreakdownchart.h>
#include <QUrl>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QHostAddress>
#include <QSslSocket>
#include <QThread>
#include <QTimer>
#include <QPdfWriter>
#include <QDateTime>
#include <QPainter>
#include <QWidget>
#include <QMediaPlayer>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtCharts/QChartView>
#include <QPrinter>
#include <QTranslator>
#include <QLibraryInfo>
#include<QSound>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->showFullScreen();
    client_ = NULL;
    son=new QSound("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/son/son1.wav");
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    /*********/ //Authentification
    ui->tableView_compte->setModel(tmpauthentification.afficher_auth());//refresh
    ui->tableView_compte_supp->setModel(tmpauthentification.afficher_auth());//refresh
    ui->tableView_compte_mod->setModel(tmpauthentification.afficher_auth());//refresh



    // Connect all signals and slots
    //connect(ui->pushButtonClear, SIGNAL(clicked(bool)), this, SLOT(clearFields()));


    // Connect all signals and slots
    connect(ui->envoyer_mail, SIGNAL(clicked(bool)), this, SLOT(sendEmail()));

    qDebug() <<"cnx ssl " << QSslSocket::supportsSsl();
    qDebug() <<"Ssl qt " << QSslSocket::sslLibraryBuildVersionString();
    qDebug() <<"openssl fi pc " << QSslSocket::sslLibraryVersionString();

    //Music
   player = new QMediaPlayer(this);
    connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::on_position_changed);
    connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::on_duration_changed);

    // CLOCK
    timer = new QTimer(this);
    connect (timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(1000);
    //Trie COMBOBOX ELEVE
    ui->combobox_trie->addItem("ID desc");
    ui->combobox_trie->addItem("ID asc");
    ui->combobox_trie->addItem("NOM");
    ui->combobox_trie->addItem("PRENOM");
    ui->combobox_trie->addItem("DATENAISSANCE");
    //Trie COMBOBOX CLASSE
    ui->combobox_trie_classe->addItem("Reference asc");
    ui->combobox_trie_classe->addItem("TYPE");
    //Trie COMBOBOX Salle
    ui->comboBox_trie_salle->addItem("NOM A-Z");
    ui->comboBox_trie_salle->addItem("NOM Z-A");
    ui->comboBox_trie_salle->addItem("ID asc");
    ui->comboBox_trie_salle->addItem("ID desc");
    ui->comboBox_trie_salle->addItem("etage asc");
    ui->comboBox_trie_salle->addItem("etage desc");
    ui->comboBox_trie_salle->addItem("ID_bat asc");
    ui->comboBox_trie_salle->addItem("ID_bat desc");
//Trie COMBOBOX SEANCE
    ui->combo_trier_seance->addItem("MATIERE A-Z");
    ui->combo_trier_seance->addItem("MARIERE Z-A");
    ui->combo_trier_seance->addItem("ID asc");
    ui->combo_trier_seance->addItem("ID desc");

    ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
    ui->tablebatiment->setModel(tmpbat.afficher());
    ui->tableupdate->setModel(tmpbat.afficher());
    ui->tablebatiment_supp->setModel(tmpbat.afficher());
    ui->tablesalle->setModel(tmpsalle.affichersalle());
    ui->tableupdatesalle->setModel(tmpsalle.affichersalle());
    ui->tablesalle_supp->setModel(tmpsalle.affichersalle());


    ui->combo_trier_batiment->addItem("NOM A-Z");
    ui->combo_trier_batiment->addItem("NOM Z-A");
    ui->combo_trier_batiment->addItem("ID asc");
    ui->combo_trier_batiment->addItem("ID desc");
    ui->combo_trier_batiment->addItem("Nbetage asc");
    ui->combo_trier_batiment->addItem("Nbetage desc");

    //refresh employe
    ui->tableview_supp_employe->setModel(tmpemploye.afficher());
    ui->tableView_modif_employe->setModel(tmpemploye.afficher());
    ui->tableView_affich_employe->setModel(tmpemploye.afficher());
    //refresh emploi
    ui->tableview_supp_emploi->setModel(tmpemplois.afficher_em());
    ui->tableView_modif_emploi->setModel(tmpemplois.afficher_em());
    ui->tableView_affiche_emploi->setModel(tmpemplois.afficher_em());

    ui->id_label_1->setMaxLength(4);
    ui->id_label_4->setMaxLength(4);
    //refresh club + equipement
    ui->tabequipement->setModel(tmpequipement.afficher());
    ui->tabclubs->setModel(tmpclubs.afficher());
    ui->tab_modifier_club->setModel(tmpclubs.afficher());
    ui->tab_modif_equipement->setModel(tmpequipement.afficher());//refresh
    ui->tab_equipement_supp->setModel(tmpequipement.afficher());//refresh
    //refreshseance
    ui->tableseance->setModel(tmpseance.afficher());//refresh
    ui->tableView_displayseance->setModel(tmpseance.afficher());//refresh
    ui->tableafficheseance->setModel(tmpseance.afficher());//refresh
    //Les images
    this->setWindowTitle("KINDERGARTEN");
    //QPixmap pix ("C:/Users/Houccem/Desktop/Kindergarten.png");
    //ui->label_pic->setPixmap(pix.scaled(216,233,Qt::KeepAspectRatio));
    QPixmap serach_icon ("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/search_icon.png");
    ui->search_icon->setPixmap(serach_icon.scaled(30,20,Qt::KeepAspectRatio));
    QPixmap serach_ele ("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/search_icon.png");
    ui->search_ele->setPixmap(serach_ele.scaled(30,20,Qt::KeepAspectRatio));
    QPixmap pix12 ("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/batiment.png");
    //ui->image_bat->setPixmap(pix2.scaled(200,233,Qt::KeepAspectRatio));
    QPixmap pix3 ("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/salle.png"); // image salle
    //ui->label_pic2->setPixmap(pix3.scaled(200,233,Qt::KeepAspectRatio));


}

MainWindow::~MainWindow()
{
    delete ui;
}
/*getstion seance***************************************************************************/
void MainWindow::on_pb_add_seance_clicked()
{
    int id = ui->spinBox_idseanceadd->value();
    int idsalle= ui->comboBox_idsalleseanceadd->currentText().toInt();
    QString matiere= ui->lineEdit_seanceadd->text();
    QSqlQuery q;
    q.prepare("select id_seance from seances ");
    q.exec();
  seance s(id,matiere,idsalle);
  bool test=false;
  if(matiere == "")
  {
      test=false;
            QMessageBox::information(nullptr, QObject::tr("Ajouter une séance"),
                            QObject::tr("Le champ matière est obligatoire.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
  {
    test=s.ajouter();
  }
  if(test)
{
      ui->tableView_displayseance->setModel(tmpseance.afficher());//refresh
      ui->tableseance->setModel(tmpseance.afficher());
      ui->tableafficheseance->setModel(tmpseance.afficher());

  QMessageBox::information(nullptr, QObject::tr("Ajouter une séance"),
                  QObject::tr("Séance ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une séance"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pb_delete_seance_clicked()
{
    int id = ui->comboBox_salleseancedelete->currentText().toInt();
    bool test=tmpseance.supprimer(id);
    if(test)
    {
        int reponse=QMessageBox::question(nullptr, "Supprimer une séance", "Voulez-vous supprimer cette séance?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes)
        {
            ui->tableseance->setModel(tmpseance.afficher());//refresh
            ui->tableView_displayseance->setModel(tmpseance.afficher());//refresh
            ui->tableafficheseance->setModel(tmpseance.afficher());//refresh
               QMessageBox::information(nullptr, QObject::tr("Supprimer une séance"),
                           QObject::tr("Séance supprimée.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
        }



    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une séance"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_update_seance_clicked()
{
    int id = ui->spinBox_idseance->value();
    int idsalle = ui->comboBox_idsalleseance->currentText().toInt();
    QString matiere=ui->lineEdit_matiereseance->text();
    seance s(id,matiere,idsalle);
   bool test=false;
   if(matiere == "")
   {
       test=false;
             QMessageBox::information(nullptr, QObject::tr("Modifier une séance"),
                             QObject::tr("Le champ matière est obligatoire.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
   }
   else
   {
       test=s.modifier();
   }
   if(test)
   {
       int reponse=QMessageBox::question(nullptr, "Modifier une séance", "Voulez-vous modifier cette séance?",
                             QMessageBox::Yes | QMessageBox::No);
       if(reponse == QMessageBox::Yes)
 {
           ui->tableseance->setModel(tmpseance.afficher());//refresh
           ui->tableView_displayseance->setModel(tmpseance.afficher());//refresh
           ui->tableafficheseance->setModel(tmpseance.afficher());//refresh
 QMessageBox::information(nullptr, QObject::tr("Modifier une séance"),
                   QObject::tr("séance modifiée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
 }
   }
   else
       QMessageBox::critical(nullptr, QObject::tr("Modifier une séance"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tabWidget_seance_tabBarClicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select id_salle from salles");
    q.exec();
    modal->setQuery(q);
    QSqlQueryModel *modal2 = new QSqlQueryModel();
    QSqlQuery q2;
    q2.prepare("select id_seance from seances");
    q2.exec();
    modal2->setQuery(q2);
    ui->comboBox_idsalleseance->setModel(modal);
    ui->comboBox_idsalleseanceadd->setModel(modal);
    ui->comboBox_salleseancedelete->setModel(modal2);

}
void MainWindow::on_tabWidget_seance_currentChanged(int index)
{
    ui->tableseance->setModel(tmpseance.afficher());//refresh
    ui->tableView_displayseance->setModel(tmpseance.afficher());//refresh
    ui->tableafficheseance->setModel(tmpseance.afficher());//refresh
}

void MainWindow::on_tabWidget_seance_tabBarClicked(int index)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID_SALLE from salles");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idsalleseance->setModel(modal);
    ui->comboBox_idsalleseanceadd->setModel(modal);
    QSqlQueryModel *modal2 = new QSqlQueryModel();
    QSqlQuery q2;
    q2.prepare("select ID_SEANCE from seances");
    q2.exec();
    modal2->setQuery(q2);
    ui->comboBox_salleseancedelete->setModel(modal2);
    ui->comboBox_pdfexcell->setModel(modal2);

}

void MainWindow::on_tableafficheseance_activated(const QModelIndex &index)
{
    QString val=ui->tableafficheseance->model()->data(index).toString();
       QSqlQuery q;
       q.prepare("select * from seances where id_seance='"+val+"'");
       if(q.exec())
       {
           while (q.next())
           {
           ui->spinBox_idseance->setValue(q.value(0).toInt());
           ui->lineEdit_matiereseance->setText(q.value(1).toString());;

           }
       }
    QSqlQueryModel *modal = new QSqlQueryModel();
      QSqlQuery q2;
      q2.prepare("select id_salle from salles");
      q2.exec();
      modal->setQuery(q2);
      ui->comboBox_idsalleseance->setModel(modal);
}
void MainWindow::on_export_excellseance_clicked()
{
    seance s;
    QString id=ui->comboBox_pdfexcell->currentText();
    son->play();
    QSqlQueryModel * model=new QSqlQueryModel();
    model=s.Find_seance(id);
    QString textData= "ID_SEANCE;MATIERE;ID_SALLE\n";
    int rows=model->rowCount();
    int columns=model->columnCount();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            textData += model->data(model->index(i,j)).toString();
            textData +=" ; ";
        }
        textData += "\n";
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
    if (!fileName.isEmpty())
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
    QFile csvfile(fileName);
    if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&csvfile);
        out<<textData;
    }
    csvfile.close();
}

void MainWindow::on_trier_seance_clicked()
{
    son->play();
    seance s;
    if( ui->combo_trier_seance->currentText() == "MATIERE A-Z")
        {ui->tableseance->setModel(s.trier_matiereasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par MATIERE asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_seance->currentText() == "MATIERE Z-A")
        {ui->tableseance->setModel(s.trier_matieredsc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par MATIERE desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_seance->currentText() == "ID asc")
        {ui->tableseance->setModel(s.trier_idasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_seance->currentText() == "ID desc") // TRIE par IDdesc
    {
        ui->tableseance->setModel(s.trier_iddesc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void MainWindow::on_exportpdf_seance_clicked()
{
    son->play();
    QPdfWriter pdf("C:/Users/User/Desktop/projet/pdf/seance.pdf");
    QPainter painter;
    if (! painter.begin(&pdf))
    {
        // failed to open file
                        qWarning("failed to open file, is it writable?");

    }
    QString id =ui->comboBox_pdfexcell->currentText();
    const time_t ctt = time(0);
    QSqlQuery query;
    query.exec("SELECT ID_SEANCE,MATIERE,ID_SALLE FROM seances WHERE ID_SEANCE='"+id+"'");

            while (query.next())
                  {

                QString id = query.value(0).toString();
                QString matiere = query.value(1).toString();
                QString idsalle= query.value(2).toString();


        painter.drawText(2200,3500,id);
        painter.drawText(2200,4000,matiere);
        painter.drawText(2200,4500,idsalle);
        painter.setPen(Qt::blue);
        painter.setPen(Qt::black);
        painter.drawText(500,2000,asctime(localtime(&ctt)));
        painter.drawText(500,3500,"Identifiant de la séance:");
        painter.drawText(500,4000,"Matière:");
        painter.drawText(500,4500,"Identifiant la salle:");




               }
             QMessageBox::information (this,"PDF","Export fait avec succès!");
}

void MainWindow::on_searchseance_textChanged(const QString &arg1)
{
    QString str=ui->searchseance->text();
    ui->tableseance->setModel(tmpseance.rechercherparmatiere(str));
}
/*****************************************************************************************************/
/******************************************************************************************************/
//gestion salles
void MainWindow::on_G_salles_clicked()                               //gestion salles
{
    QMediaPlayer *player = new QMediaPlayer;
                // ...
                player->setMedia(QUrl::fromLocalFile("C:/Users/User/Desktop/ESPRIT/2A11/QT/interfaceqt - 2/son/son1.wav"));
                player->setVolume(500);
                player->play();

    ui->stackedWidget->setCurrentIndex(5);

    ui->tablesalle->setModel(tmpsalle.affichersalle());
    ui->tableupdatesalle->setModel(tmpsalle.affichersalle());
    ui->tablesalle_supp->setModel(tmpsalle.affichersalle());
    ui->tableupdate->setModel(tmpbat.afficher());
    ui->tablebatiment->setModel(tmpbat.afficher());
    ui->tablebatiment_supp->setModel(tmpbat.afficher());

}
/*************** QUIT ************/
/****************quit*************/
void MainWindow::on_pb_quit_clicked()
{
    close();
}
void MainWindow::on_pb_quit_2_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit_3_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit_4_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit_5_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pb_quit6_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit7_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit8_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_quit9_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(1);
}
//mailingg
void MainWindow::sendEmail()
{
    // Create the email object
    Email email = createEmail();

    // Create the SMTPClient
    client_ = new SMTPClient("smtp.gmail.com",
                             465);

    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);
}

Email MainWindow::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials(ui->username->text(),
                             ui->pwd->text());

    // Create the from EmailAddress
    EmailAddress from(ui->sender->text());

    // Create the to EmailAddress
    EmailAddress to(ui->reciepient->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->subject->text(),
                ui->texture->toPlainText());

    return email;
}
void MainWindow::onStatus(Status::e status, QString errorMessage)
{
    // Show a message based on the Status
    switch (status)
    {
    case Status::Success:
        QMessageBox::information(NULL, tr("SMTPClient"), tr("Message successfully sent!"));
        break;
    case Status::Failed:
    {
        QMessageBox::warning(NULL, tr("SMTPClient"), tr("Could not send the message!"));
        qCritical() << errorMessage;
    }
        break;
    default:
        break;
    }
}


void MainWindow::on_pb_add_bat_clicked()
{
    son->play();
    int id = ui->spinBox_id->value();
    int nbetage= ui->spinBox_nbetage->value();
    QString nom= ui->nom_bat->text();
    QSqlQuery q;
    q.prepare("select ID_BATIMENT from batiments");
    q.exec();

  batiment b(id,nbetage,nom);
  bool test=false;
  if(nom == "")
  {
      test=false;
            QMessageBox::information(nullptr, QObject::tr("Ajouter un batiment"),
                            QObject::tr("Le champ nom est obligatoire.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
  }
  else
  {
    test=b.ajouter();
  }
  if(test)
{
      ui->tablebatiment->setModel(tmpbat.afficher());//refresh
      ui->tablebatiment_supp->setModel(tmpbat.afficher());
  QMessageBox::information(nullptr, QObject::tr("Ajouter un batiment"),
                  QObject::tr("Batiment ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un batiment"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_bat_clicked()
{
    son->play();
    int id = ui->comboBox_id_bat->currentText().toInt();
    bool test=tmpbat.supprimer(id);
    if(test)
    {
        int reponse=QMessageBox::question(nullptr, "Supprimer un batiment", "Voulez-vous supprimer ce batiment?",
                              QMessageBox::Yes | QMessageBox::No);
      if(reponse == QMessageBox::Yes)
      {
     ui->tablebatiment->setModel(tmpbat.afficher());//refresh
     ui->tablebatiment_supp->setModel(tmpbat.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un batiment"),
                    QObject::tr("Batiment supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un batiment"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void MainWindow::on_pb_modifier_batiment_clicked()
{
    son->play();
    int id = ui->spinBox_id_update->value();
    int nb = ui->spinBox_nbetage_update->value();
          QString nom= ui->lineEdit_nom_update->text();
          batiment b(id,nb,nom);
          bool test=false;
          if(nom == "")
          {
              test=false;
                    QMessageBox::information(nullptr, QObject::tr("Modifier un batiment"),
                                    QObject::tr("Le champ nom est obligatoire.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
          }
          else
          {
              test=b.modifier();
          }
          if(test)
          {
              int reponse=QMessageBox::question(nullptr, "Modifier un batiment", "Voulez-vous modifier ce batiment?",
                                    QMessageBox::Yes | QMessageBox::No);
              if(reponse == QMessageBox::Yes)
        {
         ui->tableupdate->setModel(tmpbat.afficher());
         ui->tablebatiment->setModel(tmpbat.afficher());
         ui->tablebatiment_supp->setModel(tmpbat.afficher());
        QMessageBox::information(nullptr, QObject::tr("Modifier un batiment"),
                          QObject::tr("batiment modifié.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
          }
          else
              QMessageBox::critical(nullptr, QObject::tr("Modifier un batiment"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tabWidgetbatiment_tabBarClicked() //pour recupperer les id dans conboBox
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID_BATIMENT from batiments");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_id_bat->setModel(modal);
    ui->comboBox_pdf->setModel(modal);


}

void MainWindow::on_tabWidgetbatiment_currentChanged()
{
    ui->tableupdate->setModel(tmpbat.afficher());//refresh
}
void MainWindow::on_tableupdate_activated(const QModelIndex &index)//pour recupperer les informations dans les lineedit pour les modifié lors du clic sur l'id
{
    QString val=ui->tableupdate->model()->data(index).toString();
        QSqlQuery q;
        q.prepare("select * from batiments where ID_BATIMENT='"+val+"'");
        if(q.exec())
        {
            while (q.next())
            {
            ui->spinBox_id_update->setValue(q.value(0).toInt());
            ui->lineEdit_nom_update->setText(q.value(1).toString());
            ui->spinBox_nbetage_update->setValue(q.value(2).toInt());


            }
        }
}

void MainWindow::on_tablebatiment_activated(const QModelIndex &index)//pour recupperer les id dans lineeditenregisterpdf
{
    QString val=ui->tablebatiment->model()->data(index).toString();
        QSqlQuery q;
        QSqlQueryModel *modal = new QSqlQueryModel();
        q.prepare("select * from batiment where id='"+val+"'");
        modal->setQuery(q);
        if(q.exec())
        {
            while (q.next())
            {
            ui->comboBox_pdf->setModel(modal);

            }
        }
}

void MainWindow::on_exportpdf_clicked()
{
    son->play();
    QPdfWriter pdf("C:/Users/User/Desktop/projet/pdf/batiment.pdf");//batiment.pdf creer lors de l'appui sur le bouton
    QPainter painter;
    if (! painter.begin(&pdf))
    {
        // failed to open file
                        qWarning("failed to open file, is it writable?");

    }
    QString id =ui->comboBox_pdf->currentText();
    const time_t ctt = time(0);
    QSqlQuery query;
    query.exec("SELECT id,nbetage,nom FROM batiments WHERE id='"+id+"'");

            while (query.next())
                  {

                QString id = query.value(0).toString();
                QString nbetage = query.value(1).toString();
                QString nom= query.value(2).toString();


        painter.drawText(2200,3500,id);
        painter.drawText(2200,4000,nbetage);
        painter.drawText(2200,4500,nom);
        painter.setPen(Qt::blue);
        painter.setPen(Qt::black);
        painter.drawText(500,2000,asctime(localtime(&ctt)));
        painter.drawText(500,3500,"Identifiant du batiment:");
        painter.drawText(500,4000,"Nombre d'étage:");
        painter.drawText(500,4500,"Nom du batiment:");




    }
             QMessageBox::information (this,"PDF","Export fait avec succès!");
}
void MainWindow::on_trier_batiment_clicked()
{
    son->play();
    batiment b;
    if( ui->combo_trier_batiment->currentText() == "NOM A-Z") // TRIE par NOMasc
        {ui->tablebatiment->setModel(b.trier_nomasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_batiment->currentText() == "NOM Z-A") // TRIE par NOMdesc
        {ui->tablebatiment->setModel(b.trier_nomdesc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_batiment->currentText() == "ID asc") // TRIE par IDasc
    {
        ui->tablebatiment->setModel(b.trier_idasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_batiment->currentText() == "ID desc") // TRIE par IDdesc
    {
        ui->tablebatiment->setModel(b.trier_iddesc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_batiment->currentText() == "Nbetage asc") // TRIE par nbetageasc
    {
        ui->tablebatiment->setModel(b.trier_nbetageasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->combo_trier_batiment->currentText() == "Nbetage desc") // TRIE par nbetagedesc
    {
        ui->tablebatiment->setModel(b.trier_nbetagedesc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_searchbat_textChanged()
{
    QString str=ui->searchbat->text();
    ui->tablebatiment->setModel(tmpbat.rechercherparnom(str));
}

/****************************gestion des salles***********************************/
void MainWindow::on_pb_add_salle_clicked()
{

    int id = ui->spinBox_idsalle->value();
    int etage= ui->spinBox_etage->value();
    QString nom= ui->lineEdit_nomsalle->text();
    int idbat = ui->comboBox_idbatsalle->currentText().toInt();
    QString etat=ui->etat1->text();
    int nbeleve=ui->spinBox_nbeleve->value();
    int classe=ui->comboBox_salle_classe->currentText().toInt();
    int employe=ui->comboBox_salle_employe->currentText().toInt();
     salle s(id,nom,etage,classe,employe,idbat,etat,nbeleve);
     bool test=false;
      son->play();
     if(nom == "")
     {
         test=false;
               QMessageBox::information(nullptr, QObject::tr("Ajouter un batiment"),
                               QObject::tr("Le champ nom est obligatoire.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else
     {
         test=s.ajoutersalle();
     }
     if(test)
   {ui->tablesalle->setModel(tmpsalle.affichersalle());//refresh
    ui->tablesalle_supp->setModel(tmpsalle.affichersalle());
   QMessageBox::information(nullptr, QObject::tr("Ajouter une salle"),
                     QObject::tr("Salle ajoutée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajouter une salle"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_salle_clicked()
{
    son->play();
    int id = ui->comboBox_id_salle->currentText().toInt();
    bool test=tmpsalle.supprimersalle(id);
    if(test)
    {
        int reponse=QMessageBox::question(nullptr, "Supprimer une salle", "Voulez-vous supprimer cette salle ?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes)
    {
            ui->tablesalle->setModel(tmpsalle.affichersalle());//refresh
            ui->tablesalle_supp->setModel(tmpsalle.affichersalle());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une salle"),
                    QObject::tr("Salle supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une salle"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pb_modifier_salle_clicked()
{
    son->play();
    int id = ui->spinBox_idsalle_update->value();
    int et= ui->spinBox_etage_update->value();
    QString nom= ui->lineEdit_nomsalle_update->text();
    int idbat = ui->comboBox_idbatsalle_update->currentText().toInt();
    QString etat=ui->etat1->text();
    int nbeleve=ui->spinBox_nbeleve_update->value();
    int classe;
    int employe;
    if(ui->etat1update->isChecked())
    {
         etat= ui->etat1update->text();
    }
    else
          etat= ui->etat0update->text();
    salle s(id,nom,et,classe,employe,idbat,etat,nbeleve);
   bool test=false;
   if(nom == "")
   {
       test=false;
             QMessageBox::information(nullptr, QObject::tr("Ajouter un batiment"),
                             QObject::tr("Le champ nom est obligatoire.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
   }
   else
   {
       test=s.modifier();
   }
   if(test)
   {
       int reponse=QMessageBox::question(nullptr, "Modifier une salle", "Voulez-vous modifier cette salle?",
                             QMessageBox::Yes | QMessageBox::No);
       if(reponse == QMessageBox::Yes)
 {
  ui->tablesalle->setModel(tmpsalle.affichersalle());
  ui->tableupdatesalle->setModel(tmpsalle.affichersalle());
  ui->tablesalle_supp->setModel(tmpsalle.affichersalle());
 QMessageBox::information(nullptr, QObject::tr("Modifier une salle"),
                   QObject::tr("salle modifiée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
 }
   }
   else
       QMessageBox::critical(nullptr, QObject::tr("Modifier une salle"),
                   QObject::tr("Erreur !.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_tabWidgetsalle_tabBarClicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select id_salle from salles");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_id_salle->setModel(modal);
    ui->comboBox_pdfsalle->setModel(modal);
    QSqlQueryModel *modal2 = new QSqlQueryModel();
    QSqlQuery q2;
    q2.prepare("select ID_BATIMENT from batiments");
    q2.exec();
    modal2->setQuery(q2);
    ui->comboBox_idbatsalle->setModel(modal2);
}

void MainWindow::on_tabWidgetsalle_currentChanged()
{
    ui->tableupdatesalle->setModel(tmpsalle.affichersalle());
}

void MainWindow::on_tableupdatesalle_activated(const QModelIndex &index) //pour recupperer les informations dans les lineedit pour les modifié lors du clic sur l'id
{

    QString val=ui->tableupdatesalle->model()->data(index).toString();
        QSqlQuery q;
        q.prepare("select * from salles where ID_SALLE='"+val+"'");
        if(q.exec())
        {
            while (q.next())
            {
            ui->spinBox_idsalle_update->setValue(q.value(0).toInt());
            ui->lineEdit_nomsalle_update->setText(q.value(1).toString());
            ui->spinBox_etage_update->setValue(q.value(2).toInt());
            ui->spinBox_nbeleve_update->setValue(q.value(7).toInt());
            }
        }
}



void MainWindow::on_tablesalle_activated(const QModelIndex &index)
{
    QString val=ui->tablesalle->model()->data(index).toString();
        QSqlQuery q;
         QSqlQueryModel *modal = new QSqlQueryModel();
        q.prepare("select * from salles where ID_SALLE='"+val+"'");
        modal->setQuery(q);
        if(q.exec())
        {
            while (q.next())
            {
            ui->comboBox_pdfsalle->setModel(modal);

            }
        }
}
void MainWindow::on_exportpdfsalle_clicked()
{
    son->play();
    QPdfWriter pdf("C:/Users/User/Desktop/projet/pdf/salle.pdf");/*batiment.pdf creer lors de l'appui sur le bouton*/
    QPainter painter;
    if (! painter.begin(&pdf))
    {
        // failed to open file
                        qWarning("failed to open file, is it writable?");

    }
    QString id =ui->comboBox_pdfsalle->currentText();
    const time_t ctt = time(0);
    QSqlQuery query;
    query.exec("SELECT ID_SALLE,NUM_ETAGE,NOM_SALLE,ID_BATIMENT_FK FROM salles WHERE ID_SALLE='"+id+"'");

            while (query.next())
                  {

                QString id = query.value(0).toString();
                QString etage = query.value(1).toString();
                QString nom= query.value(2).toString();
                 QString idbat= query.value(3).toString();

        painter.drawText(2200,3500,id);
        painter.drawText(2200,4000,etage);
        painter.drawText(2200,4500,nom);
        painter.drawText(2200,5000,idbat);
        painter.setPen(Qt::blue);
        painter.setPen(Qt::black);
        painter.drawText(500,2000,asctime(localtime(&ctt)));
        painter.drawText(500,3500,"Identifiant de la salle:");
        painter.drawText(500,4000,"Numéro d'étage:");
        painter.drawText(500,4500,"Nom de la salle:");
        painter.drawText(500,5000,"Identifiant du batiment:");



               }
             QMessageBox::information (this,"PDF","Export fait avec succès!");
}



void MainWindow::on_pb_trier_salle_clicked()
{
    son->play();
    salle s;
    if( ui->comboBox_trie_salle->currentText() == "NOM A-Z") // TRIE par NOMasc
        {ui->tablesalle->setModel(s.trier_nomasc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "NOM Z-A") // TRIE par NOMdesc
        {
        ui->tablesalle->setModel(s.trier_nomdesc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "ID asc") // TRIE par IDasc
    {
        ui->tablesalle->setModel(s.trier_idasc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "ID desc") // TRIE par IDdesc
    {
        ui->tablesalle->setModel(s.trier_iddesc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "etage asc") // TRIE par nbetageasc
    {
        ui->tablesalle->setModel(s.trier_nbetageasc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par etage asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "etage desc") // TRIE par nbetagedesc
    {
        ui->tablesalle->setModel(s.trier_nbetagedesc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par etage desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "ID_bat asc") // TRIE par idbatasc
    {
        ui->tablesalle->setModel(s.trier_idbatasc());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID_bat asc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    if( ui->comboBox_trie_salle->currentText() == "ID_bat desc") // TRIE par idbatdesc
    {
        ui->tablesalle->setModel(s.trier_nbetagedesc2());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par ID_bat desc.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_searchbat_2_textChanged()
{
    QString str=ui->searchbat_2->text();
    ui->tablesalle->setModel(tmpsalle.rechercherparnom2(str)); // recherche selon nom
}


void MainWindow::on_tabWidgetsalle_currentChanged(int index)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID_BATIMENT from BATIMENTS");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idbatsalle_update->setModel(modal);
}

void MainWindow::on_disconnect_clicked()
{
    son->play();
    ui->stackedWidget->setCurrentIndex(0);
}






void MainWindow::showtime() //Clock
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->digital_clock->setText(time_text);

}

void MainWindow::on_start_music_clicked()
{
    //Load the file
    player->setMedia(QUrl::fromLocalFile("C:/Users/Houccem/Music/Maroon 5 - Memories.mp3"));
    player->play();
    qDebug () << player->errorString();
}

void MainWindow::on_stop_music_clicked()
{
    player->stop();
}

void MainWindow::on_position_changed(qint64 position)
{
    ui->progress->setValue(position);
}

void MainWindow::on_duration_changed(qint64 position)
{
   ui->progress->setMaximum(position);
}

void MainWindow::on_progress_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_volume_sliderMoved(int position)
{
    player->setVolume(position);
}



void MainWindow::on_pushButton_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




//excell batiment/////////////////////////////////////////////

void MainWindow::on_export_excellebatiment_clicked()
{
    batiment b;
    QString id=ui->comboBox_pdf->currentText();
    son->play();
    QSqlQueryModel * model=new QSqlQueryModel();
    model=b.Find_batiment(id);
    QString textData= "Identifiant; Nom ; Nombre d'étage  \n";
    int rows=model->rowCount();
    int columns=model->columnCount();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            textData += model->data(model->index(i,j)).toString();
            textData +=" ; ";
        }
        textData += "\n";
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
    if (!fileName.isEmpty())
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
    QFile csvfile(fileName);
    if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&csvfile);
        out<<textData;
    }
    csvfile.close();
}
//excell salle/////////////////////////////////////////////
void MainWindow::on_export_excellsalle_clicked()
{
    salle s;
    QString id=ui->comboBox_pdfsalle->currentText();
    son->play();
    QSqlQueryModel * model=new QSqlQueryModel();
    model=s.Find_salle(id);
    QString textData= "ID_SALLE;NOM_SALLE;NUM_ETAGE;REF_CLASSE;ID_EMPLOYE;ID_BATIMENT;ETAT;NBELEVE\n";
    int rows=model->rowCount();
    int columns=model->columnCount();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            textData += model->data(model->index(i,j)).toString();
            textData +=" ; ";
        }
        textData += "\n";
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
    if (!fileName.isEmpty())
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
    QFile csvfile(fileName);
    if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QTextStream out(&csvfile);
        out<<textData;
    }
    csvfile.close();
}



