#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "eleve.h"
#include "classe.h"
#include "food.h"
#include "stock.h"
#include "transport.h"
#include <QMainWindow>
#include <QPainter>
#include <QMediaPlayer>
#include <QCoreApplication>
#include "SMTPClient/email.h"
#include "SMTPClient/smtpclient.h"
#include "SMTPClient/emailaddress.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendEmail();


    void onStatus(Status::e status, QString errorMessage);

    void on_G_eleves_clicked();

    void on_pushButton_ajouter_eleve_clicked();

    void on_pb_supprimer_eleve_clicked();

    void on_pb_modifier_eleve_clicked();

    void on_tab_modifier_activated(const QModelIndex &index);

    void on_tab_widget_tabBarClicked();

    void on_trier_nom_clicked();

    void on_lineEdit_rechercher_ID_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_ID_label_cursorPositionChanged();

    void on_Nom_label_cursorPositionChanged();

    void on_Prenom_label_cursorPositionChanged();

    void on_date_naiss_label_cursorPositionChanged();

    void showtime();

    void on_stat_currentChanged();

    void on_position_changed(qint64 position);

    void on_duration_changed(qint64 position);

    void on_start_music_clicked();

    void on_stop_music_clicked();

    void on_progress_sliderMoved(int position);

    void on_volume_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_pb_retourner_crud_eleve_clicked();

    void on_tab_stat_currentChanged();

    void on_pb_ajouter_classe_clicked();

    void on_pb_supprimer_classe_clicked();

    void on_tab_class_modifier_activated(const QModelIndex &index);

    void on_pushButton_modifier_7_clicked();


    void on_trier_classe_clicked();

    void on_lineEdit_rechercher_type_classe_textChanged(const QString &arg1);

    void on_stat_currentChanged(int index);

    void on_pb_imprimer_clicked();

    void on_tabeleve_activated(const QModelIndex &index);

    void on_G_salles_clicked();

    void on_G_nourriture_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_menu_supprimer_clicked();

    void on_ajouter_clicked();

    void on_aliment_supprimer_clicked();

    void on_pb_affficher_4_clicked();

    void on_pb_affficher_3_clicked();

    void on_pushButton_modifier_5_clicked();

    void on_pushButton_modifier_8_clicked();

    void on_pb_affficher_5_clicked();

    void on_pushButton_8_clicked();

    void on_lineEdit_chercher_stock_textChanged(const QString &arg1);

    void on_lineEdit_chercher_menu_textChanged(const QString &arg1);

    void on_pb_affficher_6_clicked();

    void on_id_label_1_cursorPositionChanged(int arg1, int arg2);

    void on_ID_label_2_cursorPositionChanged(int arg1, int arg2);

    void on_id_stock_supprimer_cursorPositionChanged(int arg1, int arg2);

    void on_ID_label_3_cursorPositionChanged(int arg1, int arg2);

    void on_id_label_2_cursorPositionChanged(int arg1, int arg2);

    void on_entree_label_cursorPositionChanged(int arg1, int arg2);

    void on_dessert_label_cursorPositionChanged(int arg1, int arg2);

    void on_tab_modifier_menu_activated(const QModelIndex &index);

    void on_tab_menu_supp_activated(const QModelIndex &index);

    void on_tab_aliment_supp_activated(const QModelIndex &index);

    void on_tab_modifier_stock_activated(const QModelIndex &index);

    void on_tablestock_activated(const QModelIndex &index);

    void on_imprimer_clicked();

    void on_tablemenu_activated(const QModelIndex &index);

    void on_imprimer_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_G_transport_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_modifier_3_clicked();

    void on_bus_supprimer_clicked();

    void on_tab_bus_supp_activated(const QModelIndex &index);

    void on_tab_modifier_bus_activated(const QModelIndex &index);

    void on_pushButton_modifier_nus_clicked();

    void on_pushButton_modifier_bus_clicked();

private:
    Ui::MainWindow *ui;
    TRANSPORT tmptransport;
    Eleve tmpetudiant;
    classe tmpclasse;
    food tmpfood;
    stock tmpstock;
    QTimer *timer;
    QMediaPlayer* player;
    SMTPClient *client_;
    Email createEmail();

protected:
    void paintevent(QPaintEvent *);

};
#endif // MAINWINDOW_H
