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
        Grille(QPoint pos, int tailleEnPix, QPoint entree, QPoint sortie, int nb_case);
        // Constructeur qui utilise un fichier pour generer une grille aleatoire
        // a partir d'un fichier de grille existant
        //Grille(QPoint pos, QPoint entree, QPoint sortie, int nb_case, QString nomFicher);

        void afficher(QPainter *p);

        /*QString verifierChemin();
        bool sontConnecter(const Case &c1, const Case &c2);
        Case** caseVoisine(const Case &c);
        QChar directionDeplacement(const Case &c1, const Case &c2);
        void deplacer(Case &c);*/



    private:
        QPoint pos, entree, sortie;
        int tailleEnPix;
        int nb_case;
        Case ***matrice_case;
};

#endif // GRILLE_H
