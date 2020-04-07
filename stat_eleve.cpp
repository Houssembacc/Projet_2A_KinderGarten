#include "stat_eleve.h"
#include "ui_stat_eleve.h"
#include "connexion.h"
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QGridLayout>
#include <QSqlQuery>
#include <QDebug>
#include <QWidget>
QT_CHARTS_USE_NAMESPACE

stat_eleve::stat_eleve(QWidget *eleve):
    QWidget(eleve),
    ui(new Ui::stat_eleve)
{
    ui->setupUi(this);
    QVector <QPieSlice *> tab;
        QPieSeries *series = new QPieSeries();
        QSqlQuery qry;
        int Feminin=0;
        int Masculin=0;
        int tous=0;

        qry.prepare("select * from TABLE1 ");
        if (qry.exec())
        {

            while (qry.next())
            {

    tous++;
    if (qry.value(5)=="feminin")
    {
        Feminin++;
    }
    else if(qry.value(5)=="masculin")
    {
        Masculin++;
    }


            }
        }


        qDebug () << "feminin " << Feminin;
            qDebug () << "masculin" << Masculin;


float testing1 =(Feminin*100)/tous;
QString pleasework = QString::number(testing1);
float testing2 =(Masculin*100)/tous;
QString pleasework1 = QString::number(testing2);
    series ->append("Feminin "+pleasework+"%",(Feminin));
        series ->append("Masculin "+pleasework1+"%",(Masculin));


QPieSlice * slice0= series->slices().at(0);
slice0->setLabelVisible();
QPieSlice * slice1= series->slices().at(1);
slice1->setLabelVisible();

    if (Feminin>Masculin)
    {

       slice0->setExploded();
        slice0->setPen(QPen(Qt::darkGreen,2));
       slice0->setBrush(Qt::red);

    }
    else
    {

 slice1->setExploded();
  slice1->setPen(QPen(Qt::darkGreen,2));
 slice1->setBrush(Qt::green);
    }





    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("eleve  : ");
    chart->legend()->hide();


                QChartView *chartview = new QChartView (chart);
        chartview->setRenderHint(QPainter::Antialiasing);
        QGridLayout *mainLayout = new QGridLayout;
            mainLayout->addWidget(chartview, 1, 1);
            setLayout(mainLayout);


}


stat_eleve::~stat_eleve()
{
    delete ui;
}


