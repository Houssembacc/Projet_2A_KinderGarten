#ifndef UI_STAT_ELEVE_H
#define UI_STAT_ELEVE_H


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE

class ui_stat_eleve
{
public:
    void setupUi(QWidget *stat_eleve)
    {
        if (stat_eleve->objectName().isEmpty())
            stat_eleve->setObjectName(QStringLiteral("statistique"));
        stat_eleve->setWindowModality(Qt::WindowModal);
        stat_eleve->resize(400, 300);
        retranslateUi(stat_eleve);
        QMetaObject::connectSlotsByName(stat_eleve);
    } // setupUi
    void retranslateUi(QWidget *stat_eleve)
    {
        stat_eleve->setWindowTitle(QApplication::translate("statistique", "Form", Q_NULLPTR));
    } // retranslateUi
};
namespace Ui {
    class stat_eleve: public ui_stat_eleve {};
} // namespace Ui
QT_END_NAMESPACE





#endif // UI_STAT_ELEVE_H
