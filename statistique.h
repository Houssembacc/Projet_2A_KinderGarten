#ifndef STATISTIQUE_H
#define STATISTIQUE_H


#include <QWidget>

namespace Ui {
class statistique;
}

class statistique : public QWidget
{
    Q_OBJECT

public:
    explicit statistique(QWidget *employe = nullptr);
    ~statistique();

private:
    Ui::statistique *ui;
};

#endif // statistique_H
