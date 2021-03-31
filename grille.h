///
/// \file grille.h
/// \brief La classe Grille permet de manipuler des grilles
/// \author PAULINEAU Jules,POUILLOT Samuel
/// \version 1.0
/// \date 31/03/2021
///
#ifndef GRILLE_H
#define GRILLE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>

#include <QTime>
#include<QRandomGenerator>
#include <QDateTime>
#include <iostream>

#include "case.h"
#include "caserail.h"
#include "casevide.h"

class Grille
{
    public:
        Grille();
        Grille(QPoint pos, int tailleEnPix,int nb_case);
        // Constructeur qui utilise un fichier pour generer une grille aleatoire
        // a partir d'un fichier de grille existant
        //Grille(QPoint pos, QPoint entree, QPoint sortie, int nb_case, QString nomFicher);
        //Grille* GrilleAleatoire(QPoint pos, int tailleEnPix,int nb_case);
        QString verifierChemin();
        QChar sontConnecter(QPoint posCour, QPoint posSuiv);
        std::vector<QPoint> PosVoisine(QPoint pos);
        QChar directionDeplacement(const CaseRail &c1, const CaseRail &c2);
        void deplacer(Case &c);

        void afficher(QPainter *p);

        //getters et setters
        int getNbCase();
        Case*** getMatrice();
        QPoint getPos();

    private:

        QPoint pos;
        int tailleEnPix;
        int nb_case;
        Case ***matrice_case;
};

#endif // GRILLE_H
