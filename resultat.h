#ifndef RESULTAT_H
#define RESULTAT_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class Resultat;
}

class Resultat : public QDialog
{
    Q_OBJECT

public:
    explicit Resultat(QWidget *parent = nullptr);
    Resultat(bool gagne, QWidget *parent = nullptr);
    ~Resultat();

private slots:

private:
    Ui::Resultat *ui;
    void paintEvent(QPaintEvent* e);
    bool m_gagne;
};

#endif // RESULTAT_H
