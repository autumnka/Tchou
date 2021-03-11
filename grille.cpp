#include "grille.h"
#include <QtGui>
Grille::Grille(QPoint pos, int tailleEnPix,QPoint entree, QPoint sortie, int nb_case)
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

// Constructeur qui utilise un fichier pour generer une grille aleatoire
// a partir d'un fichier de grille existant
/*Grille::Grille(QPoint pos, QPoint entree, QPoint sortie, int nb_case, QString nomFicher)
{

}*/

QString Grille::verifierChemin()
{
    bool continuer=true;
    bool valide=false;

    CaseRail* caseEntree=new CaseRail(1, entree,1);
    CaseRail* caseSortie=new CaseRail(1, sortie,1);
    CaseRail* case_courante = caseEntree;
    CaseRail* case_precedente;
    QString retour, instructionDeplacement;
    //on verifie que le chemin commence bien au départ (pas sûr que ce soit nécessaire)
    if(!sontConnecter(*case_courante, *caseEntree)){
        continuer=false;
        //renvoyer position case_courante
    }
    else{
        do{
            //on parcours les cases voisines sauf la case precedentes
            //une case rail ne peut être connectée qu'à 2 autres cases au max
            int i=0;
            while((caseVoisine(*case_courante)[i]!=case_precedente)&&(!sontConnecter(*case_courante, *caseVoisine(*case_courante)[i]))&&(i<5)){
                i++;
            }
            //si aucune case voisine n'est connectée
           if(i==5){
               continuer = false;
                valide = false;
            }
           else{
                //on renseigne la direction du deplacement vers la case connectée
                instructionDeplacement+=directionDeplacement(*case_courante, *caseVoisine(*case_courante)[i]);
                case_precedente = case_courante;
                case_courante= caseVoisine(*case_courante)[i];
                //on s'arrete sur la case adjacente à la case sortie
                if(sontConnecter(*case_courante, *caseSortie)){
                    continuer = false;
                    valide = true;
                }
           }
        }while(continuer);
    }
    //le premier caractère est 0 si le chemin n'est pas valide, 1 sinon
    retour=QString::number(valide);
    //on indique ensuite la position de la case sur laquelle le chemin s'arrête
    retour+=QString::number(case_courante->getPosition().rx())+QString::number(case_courante->getPosition().ry());
    //et les instructions de déplacements pour le chemin
    retour+=instructionDeplacement;
    return retour;
}

bool Grille::sontConnecter(const CaseRail &c1, const CaseRail &c2)
{
    CaseRail* vois= *caseVoisine((CaseRail)c1);
    for(int i=0;i<5;i++){
        if(c2.getPosition()==(vois[i]).getPosition()) return true;
    }
    return false;
}

CaseRail** Grille::caseVoisine(const CaseRail &c)
{
    //il faut gérer les exceptions sur les bords

    CaseRail** ens;
    int k=0;
    //on parcours les cases
    for(int i=c.getPosition().rx()-1;i<=c.getPosition().rx()+1;i++){
        for(int j=c.getPosition().ry()-1;j<=c.getPosition().ry()+1;j++){
            if((i!=c.getPosition().rx())&(j!=c.getPosition().ry())){
                ens[k]=new CaseRail(matrice_case[i][j]->getType(),matrice_case[i][j]->getPosition(),matrice_case[i][j]->getTaille());
                k++;
            }
        }
    }
    return ens;
}
//retourne la direction de la case 1 à la case 2
//h: haut, b:bas, d:droite, g:gauche
QChar Grille::directionDeplacement(const CaseRail &c1, const CaseRail &c2)
{
   if(!sontConnecter(c1,c2)){
    int diff=10*(c1.getPosition().rx()-c2.getPosition().rx())+(c1.getPosition().ry()-c1.getPosition().ry());
    switch(diff){
        //c1 est a gauche de c2
        case -1:return 'd';
                break;
        //c1 est a droite de c2
        case 1:return 'g';
                break;
        //c1 est au dessus de c2
        case -10:return 'b';
                break;
        //c1 est en dessous de c2
        case 10:return 'h';
                break;
    }
   }
   return 'd'; //par défaut
}

void Grille::deplacer(CaseRail &c)
{
    //on va deplacer la case si ce n'est pas la case vide
    //on cherche la position de la case vide
    int i=0,j=0;
    while((i<nb_case)&&((matrice_case[i][j])->getType()!=0)){
        //on parcours ligne par ligne la matrice des cases
        if(j<nb_case-1) j++;
        else{
            //on passe  à la ligne suivante
            j=0;
            i++;
        }
    }
    c.echanger(*matrice_case[i][j]);
}
