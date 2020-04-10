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
