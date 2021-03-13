#ifndef GRILLE_H
#define GRILLE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "case.h"
#include "caserail.h"
#include "casevide.h"

class Grille
{
    public:
        Grille();
        Grille(QPoint pos, int tailleEnPix,QPoint entree, QPoint sortie, int nb_case);
        // Constructeur qui utilise un fichier pour generer une grille aleatoire
        // a partir d'un fichier de grille existant
        //Grille(QPoint pos, QPoint entree, QPoint sortie, int nb_case, QString nomFicher);

        QString verifierChemin();
        bool sontConnecter(const CaseRail &c1, const CaseRail &c2);
        CaseRail** caseVoisine(const CaseRail &c);
        QChar directionDeplacement(const CaseRail &c1, const CaseRail &c2);
        void deplacer(Case &c);

        void afficher(QPainter *p);

        //getters et setters
        int getNbCase();
        Case*** getMatrice();
        QPoint getPos();

    private:

        QPoint pos;
        QPoint *entree= new QPoint(150,50);
        QPoint *sortie= new QPoint(650,550);
        int tailleEnPix;
        int nb_case;
        Case ***matrice_case;
};

#endif // GRILLE_H
