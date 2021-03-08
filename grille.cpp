#include "grille.h"


#include <QtGui>

// Constructeur qui utilise un fichier pour generer une grille aleatoire
// a partir d'un fichier de grille existant
Grille::Grille(QPoint pos, int tailleEnPix, QPoint entree, QPoint sortie, int nb_case)
{
    this->pos = pos;
    this->tailleEnPix = tailleEnPix;
    this->entree = entree;
    this->sortie = sortie;
    this->nb_case = nb_case;

    matrice_case = new Case**[nb_case];
    for (int i=0; i<nb_case; ++i)
    {
        matrice_case[i] = new Case*[nb_case];
        for (int j=0; j<nb_case; ++j)
            matrice_case[i][j] = NULL;
    }

    int t_c = tailleEnPix/nb_case;

    if (nb_case == 2)
    {
        matrice_case[0][0] = new CaseRail(5, pos, t_c);
        matrice_case[0][1] = new CaseVide(0, QPoint(pos.x()+t_c, pos.y()), t_c);
        matrice_case[1][0] = new CaseRail(3, QPoint(pos.x(), pos.y()+t_c), t_c);
        matrice_case[1][1] = new CaseRail(1, QPoint(pos.x()+t_c, pos.y()+t_c), t_c);
    }

    if (nb_case == 3)
    {
        matrice_case[0][0] = new CaseRail(1, QPoint(pos.x(), pos.y()), t_c);
        matrice_case[0][1] = new CaseRail(5, QPoint(pos.x()+t_c, pos.y()), t_c);
        matrice_case[1][1] = new CaseRail(2, QPoint(pos.x()+t_c, pos.y()+t_c), t_c);
        matrice_case[2][1] = new CaseRail(3, QPoint(pos.x()+t_c, pos.y()+2*t_c), t_c);
        matrice_case[2][2] = new CaseRail(1, QPoint(pos.x()+2*t_c, pos.y()+2*t_c), t_c);

        matrice_case[0][2] = new CaseVide(0, QPoint(pos.x()+2*t_c, pos.y()), t_c);
        matrice_case[1][0] = new CaseRail(1, QPoint(pos.x(), pos.y()+t_c), t_c);
        matrice_case[2][0] = new CaseRail(1, QPoint(pos.x(), pos.y()+2*t_c), t_c);
        matrice_case[1][2] = new CaseRail(1, QPoint(pos.x()+2*t_c, pos.y()+t_c), t_c);
    }

}

void Grille::afficher(QPainter *p)
{
    for (int i = 0; i<nb_case; ++i)
    {
        for (int j = 0; j<nb_case; ++j)
            matrice_case[i][j]->afficher(p);
    }
}
/*
QString Grille::verifierChemin()
{
    return "";
}

bool Grille::sontConnecter(const Case &c1, const Case &c2)
{
    Case* vois= *caseVoisine(c1);

    for(int i=0;i<5;i++){

        if(c2.getPosition()==(vois[i]).getPosition()) return true;

    }
    return false;
}

Case** Grille::caseVoisine(const Case &c)
{
    //il faut gérer les exceptions sur les bords
    Case** ens;
    int k=0;

    //on parcours les cases

    for(int i=c.getPosition().rx()-1;i<=c.getPosition().rx()+1;i++){

        for(int j=c.getPosition().ry()-1;j<=c.getPosition().ry()+1;j++){

            if((i!=c.getPosition().rx())&(j!=c.getPosition().ry())){
                ens[k]=matrice_case[i][j];
                k++;
            }
        }
    }
    return ens;
}
QChar Grille::directionDeplacement(const Case &c1, const Case &c2)
{
   if(!sontConnecter(c1,c2))
   {
    int diff=10*(c1.getPosition().rx()-c2.getPosition().rx())+(c1.getPosition().ry()-c1.getPosition().ry());

    switch(diff){

        //c1 est a gauche de c2

        case -1:return 'd';

        break;

        //c1 est a droite de c2

        case 1:return 'g';

        break;

        //c1 est au dessus de c2

        case -10:return 'd';

        break;

        //c1 est en dessous de c2

        case 10:return 'b';

        break;
    }
   }

   return 'd';
}



void Grille::deplacer(Case &c)
{

}
*/
