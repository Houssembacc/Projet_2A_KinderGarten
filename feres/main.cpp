#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexion c;

    MainWindow w;
    bool test=c.ouvrirConnexion();
    if(test)
    {
        w.show();
        /*QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection avec succés.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
