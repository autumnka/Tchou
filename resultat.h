///
/// \file resultat.h
/// \brief La classe Resultat permet de manipuler la fenetre resultat
/// \author PAULINEAU Jules,POUILLOT Samuel
/// \version 1.0
/// \date 31/03/2021
///
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

    int getAction();

private slots:

    void on_pushButton_quitter_clicked();

    void on_pushButton_continuer_clicked();

    void on_pushButton_recommencer_clicked();

private:
    Ui::Resultat *ui;
    void paintEvent(QPaintEvent* e);
    bool m_gagne;

    /* action vaut 0 si quitter, 1 si continuer, 2 si recommencer */
    int action = -1;
};

#endif // RESULTAT_H
