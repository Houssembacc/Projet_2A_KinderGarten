#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "eleve.h"
#include "classe.h"
#include "food.h"
#include "stock.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client_ = NULL;

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
    ui->combobox_trie->addItem("NOM");
    ui->combobox_trie->addItem("PRENOM");
    ui->combobox_trie->addItem("DATENAISSANCE");
    //Trie COMBOBOX CLASSE
    ui->combobox_trie_classe->addItem("ID");
    ui->combobox_trie_classe->addItem("TYPE");

    ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
    ui->stackedWidget->setCurrentIndex(0);// mainpage (ouverture)
    //Les images
    this->setWindowTitle("KINDERGARTEN");
    QPixmap pix ("C:/Users/Houccem/Desktop/Kindergarten.png");
    ui->label_pic->setPixmap(pix.scaled(216,233,Qt::KeepAspectRatio));
    QPixmap pix2 ("C:/Users/Houccem/Desktop/eleve.jpg");
    ui->eleve_png->setPixmap(pix2.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap serach_icon ("C:/Users/Houccem/Desktop/search_icon.png");
    ui->search_icon->setPixmap(serach_icon.scaled(30,20,Qt::KeepAspectRatio));
    QPixmap serach_ele ("C:/Users/Houccem/Desktop/search_icon.png");
    ui->search_ele->setPixmap(serach_ele.scaled(30,20,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//gestion salles
void MainWindow::on_G_salles_clicked()                               //gestion salles
{
    ui->stackedWidget->setCurrentIndex(4);
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

void MainWindow::on_G_eleves_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabeleve->setModel(tmpetudiant.afficher());
    ui->tab_eleve_supp->setModel(tmpetudiant.afficher());
    ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
    ui->tabclasse->setModel(tmpclasse.afficher_classe());
    ui->tab_class_supp->setModel(tmpclasse.afficher_classe());
    ui->tab_class_modifier->setModel(tmpclasse.afficher_classe());//refresh
    // **********************************************************************//

    //************************************************************************//


    //combobox classe supprimer
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q0;
    q0.prepare("select REFERENCE from CLASSES");
    q0.exec();
    model->setQuery(q0);
    ui->combobox_class_supp->setModel(model);
    //combobox ajouter eleve
    QSqlQueryModel *modele = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select REFERENCE from CLASSES");
    q.exec();
    modele->setQuery(q);
    ui->combobox_ajouter->setModel(modele);

/*
QMediaPlayer *player = new QMediaPlayer;
            // ...
            player->setMedia(QUrl::fromLocalFile("C:/Users/Houccem/Desktop/so_cute.wav"));
            player->setVolume(500);
            player->play();
*/

}

void MainWindow::on_pushButton_ajouter_eleve_clicked()
{
    int id = ui->ID_label->text().toInt();
    int reference= ui->combobox_ajouter->currentText().toInt();
    QString nom= ui->Nom_label->text();
    QString prenom= ui->Prenom_label->text();
    QString adresse= ui->adresse_label->text();
    QString datenaissance= ui->date_naiss_label->text();
    QString sexe= ui->feminin->text();
    if(ui->feminin->isChecked())
    {
         sexe= ui->feminin->text();
    }
    else
          sexe= ui->masculin->text();

    Eleve e(id,nom,prenom,adresse,datenaissance,sexe,reference); // appel au contructeur paramétré...
    bool test=e.ajouter();
    if(test)
    {ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
     ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
     ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh

    QMessageBox::information(nullptr, QObject::tr("Ajouter un étudiant"),
                      QObject::tr("Etudiant ajouté.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un étudiant"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


}


void MainWindow::on_pb_supprimer_eleve_clicked()
{
    int id = ui->comboBox->currentText().toInt();
    bool test=tmpetudiant.supprimer(id);
    if(test)
    {ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
     ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
     ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Etudiant supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pb_modifier_eleve_clicked()
{
    int id = ui->ID_modif_label->text().toInt();
    int reference = ui->combo_modifier_eleve->currentText().toInt();
    QString nom= ui->Nom_modif_label->text();
    QString prenom= ui->Prenom_modif_label->text();
    QString date_naissance= ui->date_naiss_modif_label->text();
    QString adresse= ui->adress_modif_label->text();
    QString sexe= ui->radioButton_feminen_5->text();


    if(ui->radioButton_feminen_5->isChecked())
    {
         sexe= ui->radioButton_feminen_5->text();
    }
    else
          sexe= ui->radioButton_masculin_5->text();


  Eleve e(id,nom,prenom,adresse,date_naissance,sexe,reference);
  bool test=e.update();
  if(test)
{
      ui->tabeleve->setModel(tmpetudiant.afficher());
      ui->tab_modifier->setModel(tmpetudiant.afficher());
      ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh


QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                  QObject::tr("employe modifie.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_tab_modifier_activated(const QModelIndex &index)
{

    QString val=ui->tab_modifier->model()->data(index).toString();
        QSqlQuery q;
        q.prepare("select * from TABLE1 where ID='"+val+"'");
        if(q.exec())
        {
            while (q.next())
            {
            ui->ID_modif_label->setText(q.value(0).toString());
            ui->Nom_modif_label->setText(q.value(1).toString());
            ui->Prenom_modif_label->setText(q.value(2).toString());
            ui->adress_modif_label->setText(q.value(3).toString());
            ui->date_naiss_modif_label->setText(q.value(4).toString());
            ui->combo_modifier_eleve->setCurrentText(q.value(6).toString());
            if(q.value(5) == "masculin")
            {
                ui->radioButton_masculin_5->setChecked(1);
            }
            else
                ui->radioButton_feminen_5->setChecked(1);
        }
            //combobox ajouter eleve
            QSqlQueryModel *modele = new QSqlQueryModel();
            QSqlQuery q;
            q.prepare("select REFERENCE from CLASSES");
            q.exec();
            modele->setQuery(q);
            ui->combo_modifier_eleve->setModel(modele);
}
}



void MainWindow::on_tab_widget_tabBarClicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select ID from TABLE1");
    q.exec();
    modal->setQuery(q);
    ui->comboBox->setModel(modal);
}

void MainWindow::on_trier_nom_clicked()
{
    Eleve e;
    if( ui->combobox_trie->currentText() == "NOM") // TRIE par NOM
        {ui->tabeleve->setModel(e.trier_nom());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Nom.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    if( ui->combobox_trie->currentText() == "PRENOM") // TRIE par PRENOM
    {
        ui->tabeleve->setModel(e.trier_prenom());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Prenom.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

void MainWindow::on_lineEdit_rechercher_ID_textChanged(const QString &arg1)
{
    QString str=ui->lineEdit_rechercher_ID->text();
    ui->tabeleve->setModel(tmpetudiant.recherchernom(str));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//control de saisie
void MainWindow::on_ID_label_cursorPositionChanged() //control de saisie
{
    QRegExp rx("^[0-9]*$");
    QRegExpValidator  *validID = new QRegExpValidator(rx,this);
    ui->ID_label->setValidator(validID);
}

void MainWindow::on_Nom_label_cursorPositionChanged() //control de saisie
{
    QRegExp rx("^[A-Za-z]*$");
    QRegExpValidator  *validNOM = new QRegExpValidator(rx,this);
    ui->Nom_label->setValidator(validNOM);
}

void MainWindow::on_Prenom_label_cursorPositionChanged() //control de saisie
{
    QRegExp rx("^[A-Za-z]*$");
    QRegExpValidator  *validPRENOM = new QRegExpValidator(rx,this);
    ui->Prenom_label->setValidator(validPRENOM);
}

void MainWindow::on_date_naiss_label_cursorPositionChanged() //control de saisie
{
    QRegExp rx("^[0-9/0-9/0-9]*$");
    QRegExpValidator  *validDN = new QRegExpValidator(rx,this);
    ui->date_naiss_label->setValidator(validDN);
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
    player->setMedia(QUrl::fromLocalFile("C:/Users/Houccem/Music/50 Cent - Candy Shop (Clymed Remix).mp3"));
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

void MainWindow::on_stat_currentChanged()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    //![1]
    QSqlQuery q,q1,q2,q3,q4;
    q3.prepare("select SEXE from TABLE1 where SEXE='masculin'");
    q4.prepare("select SEXE from TABLE1 where SEXE='feminin'");
    q.prepare("select * from TABLE1");
    q1.prepare("select * from TABLE1 where SEXE='feminin'");
    q2.prepare("select * from TABLE1 where SEXE='masculin'");
    if(q.exec())
    {
        int c=0; int b=0;
        while(q.next())
        {
            b=b+1; //total des eleves..

        }
    if(q1.exec())
    {
        int c=0,a=0;
        while(q1.next()) //totale des feminins
        {
            a=a+1;
        }

    if(q2.exec())
    {
        int c=0,d=0;
        while(q2.next()) //total des masculins
        {
            d=d+1;
        }

    if(q3.exec())
    {

        while(q3.next()) //total des masculins
        {
            QString masculin=q3.value(0).toString();
        }

    if(q4.exec())
    {

        while(q4.next()) //total des masculins
        {
           QString feminin=q4.value(0).toString();
        }

    float fm=(b/a)*100;
    float ms=(d/a)*100;
    QString feminin=q4.value(0).toString();
    QString masculin=q3.value(0).toString();


        QPieSlice *slice = series->append("Feminin",fm);
        QPieSlice *slice2 = series->append("Masculin",ms);

        slice->setExploded();
        slice->setLabelVisible();

    //![2]


    //![2]

    //![3]
    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);
}
}}}}}
void MainWindow::on_pushButton_clicked() //Click sur STATISTIQUES
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pb_retourner_crud_eleve_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tab_stat_currentChanged()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    //![1]
    QSqlQuery q;
    q.prepare("select ID,NOM from TABLE1");
    if(q.exec())
    {
        int c=0;
        while(q.next())
        {
            int a= q.value(0).toInt();
            QString b= q.value(1).toString();
            if(c == 0)
            {
                QPieSlice *slice = series->append(b,a);
                slice->setExploded();
                slice->setLabelVisible();
            }
            else
                  series->append(b,a);

        }
    }
    //![2]


    //![2]

    //![3]
    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeDark);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontal_sexe);
}

void MainWindow::on_pb_ajouter_classe_clicked()
{
    int ref = ui->Ref_classe_label->text().toInt();
    QString type= ui->type_classe_label->text();

    classe cl(ref,type); // appel au contructeur paramétré...
    bool test=cl.ajouter_classe();
    if(test)
    {ui->tabclasse->setModel(tmpclasse.afficher_classe());//refresh
     ui->tab_class_supp->setModel(tmpclasse.afficher_classe());//refresh
     ui->tab_class_modifier->setModel(tmpclasse.afficher_classe());//refresh
    QMessageBox::information(nullptr, QObject::tr("Ajouter un étudiant"),
                      QObject::tr("Classe ajoutée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un étudiant"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    //combobox de ajouter eleve
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q1;
    q1.prepare("select REFERENCE from CLASSES");
    q1.exec();
    modal->setQuery(q1);
    ui->combobox_ajouter->setModel(modal);
    //combobox de supprimer classe
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery q0;
    q0.prepare("select REFERENCE from CLASSES");
    q0.exec();
    model->setQuery(q0);
    ui->combobox_class_supp->setModel(model);
}

void MainWindow::on_pb_supprimer_classe_clicked()
{
    int ref = ui->combobox_class_supp->currentText().toInt();
    bool test=tmpclasse.supprimer_classe(ref);
    if(test)
    {ui->tabclasse->setModel(tmpclasse.afficher_classe());//refresh
     ui->tab_class_supp->setModel(tmpclasse.afficher_classe());//refresh
     ui->tab_class_modifier->setModel(tmpclasse.afficher_classe());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Etudiant supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tab_class_modifier_activated(const QModelIndex &index)
{
    QString val=ui->tab_class_modifier->model()->data(index).toString();
        QSqlQuery q;
        q.prepare("select * from CLASSES where REFERENCE='"+val+"'");
        if(q.exec())
        {
            while (q.next())
            {
                ui->Ref_classe_modif_label->setText(q.value(0).toString());
                ui->type_classe_modif_label->setText(q.value(1).toString());

            }
        }
}

void MainWindow::on_pushButton_modifier_7_clicked()
{
    int ref = ui->Ref_classe_modif_label->text().toInt();
    QString type= ui->type_classe_modif_label->text();



  classe cl(ref,type);
  bool test=cl.update_classe();
  if(test)
{
      ui->tabclasse->setModel(tmpclasse.afficher_classe());
      ui->tab_class_modifier->setModel(tmpclasse.afficher_classe());
      ui->tab_class_supp->setModel(tmpclasse.afficher_classe());//refresh


QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                  QObject::tr("Classe modifiee.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_trier_classe_clicked()
{
    classe c;
    if( ui->combobox_trie_classe->currentText() == "ID") // TRIE par ID
        {ui->tabclasse->setModel(c.trier_id());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table triee par ID.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    if( ui->combobox_trie_classe->currentText() == "TYPE") // TRIE par TYPE
    {
        ui->tabclasse->setModel(c.trier_type());
        QMessageBox::information(nullptr, QObject::tr("Trier"),
                              QObject::tr("Table trie par Type.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void MainWindow::on_lineEdit_rechercher_type_classe_textChanged(const QString &arg1)
{
    QString str=ui->lineEdit_rechercher_type_classe->text();
    ui->tabclasse->setModel(tmpclasse.recherchertype(str));
}

//tab supprimer eleve
void MainWindow::on_stat_currentChanged(int index)
{
    //combobox de Supprimer eleve
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery q1;
    q1.prepare("select ID from TABLE1");
    q1.exec();
    modal->setQuery(q1);
    ui->comboBox->setModel(modal);
}

void MainWindow::on_pb_imprimer_clicked()
{

    QPdfWriter pdf("C:/Users/file.pdf");
    QPainter painter(&pdf);
    painter.setPen(Qt::blue);
    painter.drawText(100,600,"Houssembaccouche");

    QString id =ui->line_pdf->text();
       const time_t ctt = time(0);
       QSqlQuery query;
       query.exec("SELECT * FROM TABLE1 WHERE id='"+id+"'");

               while (query.next())
                     {

                   QString id = query.value(0).toString();
                   QString nom = query.value(1).toString();
                   QString prenom= query.value(2).toString();
                   QString adresse= query.value(3).toString();
                   QString datenaiss= query.value(4).toString();
                   QString sexe= query.value(5).toString();


           painter.drawText(2200,3500,id);
           painter.drawText(2200,4000,nom);
           painter.drawText(2200,4500,prenom);
           painter.drawText(2200,5000,adresse);
           painter.drawText(2200,5500,datenaiss);
           painter.drawText(2200,6000,sexe);
           painter.setPen(Qt::blue);
           painter.setPen(Qt::black);
           painter.drawText(500,2000,asctime(localtime(&ctt)));
           painter.drawText(500,3500,"Identifiant d'élève:");
           painter.drawText(500,4000,"Nm élève:");
           painter.drawText(500,4500,"Prenom élève:");
           painter.drawText(500,5000,"Adresse:");
           painter.drawText(500,5500,"Date de naissance:");
           painter.drawText(500,6000,"Sexe:");




       }
                QMessageBox::information (this,"PDF","Export fait avec succès!");

}

void MainWindow::on_tabeleve_activated(const QModelIndex &index)
{
    QString val=ui->tabeleve->model()->data(index).toString();
           QSqlQuery q;
           q.prepare("select * from TABLE1 where ID='"+val+"'");
           if(q.exec())
           {
               while (q.next())
               {
                    ui->line_pdf->setText(q.value(0).toString());

               }
           }
}


//menu et nouriture

void MainWindow::on_G_nourriture_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tablemenu->setModel(tmpfood.afficher());
    ui->tablestock->setModel(tmpstock.afficher());
}

void MainWindow::on_pushButton_modifier_2_clicked()
{
    int id = ui->id_label_1->text().toInt();
    //int reference= ui->combobox_ajouter->currentText().toInt();
    QString entree= ui->entree_label->text();
    QString plat= ui->plat_label->text();
    QString dessert= ui->dessert_label->text();
    QString Jour= ui->Jour_label->text();

        food f(entree,plat,dessert,Jour,id); // appel au contructeur paramétré...
        bool test=f.ajouter();
        if(test)
        {//ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
         //ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
         //ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh

        QMessageBox::information(nullptr, QObject::tr("Ajouter un menu"),
                          QObject::tr("menu ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un menu"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);




}

void MainWindow::on_menu_supprimer_clicked()
{
    QString jour = ui->jour_supprimer->text();
    bool test=tmpfood.supprimer(jour);
    if(test)
    {//ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
     //ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
     //ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un menu"),
                    QObject::tr("menu supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_ajouter_clicked()
{
    int qte = ui->qte_label->text().toInt();
        //int reference= ui->combobox_ajouter->currentText().toInt();
        QString id= ui->ID_label_2->text();
        QString nom= ui->Nom_label_2->text();
        QString type= ui->gouter->text();
        if(ui->gouter->isChecked())
        {
             type= ui->gouter->text();
        }
        else if(ui->fruits->isChecked())
        {
              type= ui->fruits->text();
        }
        else
        {
            type= ui->legumes->text();
        }


        stock s(id,nom,type,qte); // appel au contructeur paramétré...
        bool test=s.ajouter();
        if(test)
        {//ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
         //ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
         //ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh

        QMessageBox::information(nullptr, QObject::tr("Ajouter un menu"),
                          QObject::tr("menu ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
              QMessageBox::critical(nullptr, QObject::tr("Ajouter un menu"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tablestock->setModel(tmpstock.afficher());
}


void MainWindow::on_aliment_supprimer_clicked()
{
    QString id = ui->id_stock_supprimer->text();
    bool test=tmpstock.supprimer(id);
    if(test)
    {//ui->tabeleve->setModel(tmpetudiant.afficher());//refresh
     //ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh
     //ui->tab_modifier->setModel(tmpetudiant.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer element"),
                    QObject::tr("element supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer element"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_affficher_4_clicked()
{
    ui->tablestock->setModel(tmpstock.afficher());
}

void MainWindow::on_pb_affficher_3_clicked()
{
    ui->tablemenu->setModel(tmpfood.afficher());
}

void MainWindow::on_pushButton_modifier_5_clicked()
{
        int id = ui->id_label_2->text().toInt();
        QString entree= ui->entree_label_2->text();
        QString plat= ui->plat_label_2->text();
        QString dessert= ui->dessert_label_2->text();
        QString Jour= ui->Jour_label_2->text();
        /*food f(entree,plat,dessert,Jour,id); // appel au contructeur paramétré...
        bool test=f.modifier();*/
        food f(entree,plat,dessert,Jour,id); // appel au contructeur paramétré...
        bool test=f.update();
        if(test)

    {
          /*ui->tabeleve->setModel(tmpetudiant.afficher());
          ui->tab_modifier->setModel(tmpetudiant.afficher());
          ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh*/


    QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                      QObject::tr("employe modifie.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}
//modifier menu
void MainWindow::on_pushButton_modifier_8_clicked()
{
    int qte = ui->qte_label_2->text().toInt();
            //int reference= ui->combobox_ajouter->currentText().toInt();
            QString id= ui->ID_label_3->text();
            QString nom= ui->Nom_label_3->text();
            QString type= ui->gouter_2->text();
            if(ui->gouter_2->isChecked())
            {
                 type= ui->gouter_2->text();
            }
            else if(ui->fruits_2->isChecked())
            {
                  type= ui->fruits_2->text();
            }
            else
            {
                type= ui->legumes_2->text();
            }
            stock s(id,nom,type,qte); // appel au contructeur paramétré...
            bool test=s.update();
            if(test)

        {
              /*ui->tabeleve->setModel(tmpetudiant.afficher());
              ui->tab_modifier->setModel(tmpetudiant.afficher());
              ui->tab_eleve_supp->setModel(tmpetudiant.afficher());//refresh*/


        QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                          QObject::tr("employe modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

        }
          else
              QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}
//trie menu
void MainWindow::on_pb_affficher_5_clicked()
{
    if(ui->combobox_trie_2->currentText() == "ID")
    {
        ui->tablemenu->setModel(tmpfood.trier_id());
    }
    if(ui->combobox_trie_2->currentText() == "plat principale")
    {
        ui->tablemenu->setModel(tmpfood.trier_plat());
    }
    if(ui->combobox_trie_2->currentText() == "jour")
    {
        ui->tablemenu->setModel(tmpfood.trier_jour());
    }

}
