#ifndef PARTIE_H
#define PARTIE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "feu.h"
#include "train.h"
#include "mainwindow.h"

//#include "grille.h"
class Partie
{
public:
    //constructeurs
    Partie(bool resultat, int niveau, int nbCase, bool partieEnCours);
    Partie(const Partie& p);
    //bool CheminValide();
    bool continuer();
    bool lancerTrain();
    QString trajectoire();
    void appuyerFeu();

private:
    bool m_resultat;
    int m_niveau;
    int m_nbCase;
    bool m_partieEnCours;
    //Grille* m_grille;
    Feu* m_feu;
    Train* m_train;
};

#endif // PARTIE_H
