#include "grille.h"
#include <QtGui>
#include <QDebug>

Grille::Grille()
{

}

Grille::Grille(QPoint pos, int tailleEnPix,int nb_case)
{
    this->pos = pos;
    this->tailleEnPix = tailleEnPix;
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
        matrice_case[0][1] = new CaseRail(3, QPoint(pos.x()+t_c, pos.y()), t_c);
        matrice_case[1][0] = new CaseRail(1, QPoint(pos.x(), pos.y()+t_c), t_c);
        matrice_case[1][1] = new CaseVide(0, QPoint(pos.x()+t_c, pos.y()+t_c), t_c);

    }

    if (nb_case == 3)
    {
        matrice_case[0][0] = new CaseRail(1, QPoint(pos.x(), pos.y()), t_c);
        matrice_case[0][1] = new CaseRail(2, QPoint(pos.x()+t_c, pos.y()), t_c);
        matrice_case[1][1] = new CaseVide(0, QPoint(pos.x()+t_c, pos.y()+t_c), t_c);
        matrice_case[2][1] = new CaseRail(3, QPoint(pos.x()+t_c, pos.y()+2*t_c), t_c);
        matrice_case[2][2] = new CaseRail(1, QPoint(pos.x()+2*t_c, pos.y()+2*t_c), t_c);

        matrice_case[0][2] = new CaseRail(5, QPoint(pos.x()+2*t_c, pos.y()), t_c);
        matrice_case[1][0] = new CaseRail(1, QPoint(pos.x(), pos.y()+t_c), t_c);
        matrice_case[2][0] = new CaseRail(1, QPoint(pos.x(), pos.y()+2*t_c), t_c);
        matrice_case[1][2] = new CaseRail(1, QPoint(pos.x()+2*t_c, pos.y()+t_c), t_c);
    }
}

/*Grille* Grille::GrilleAleatoire(QPoint pos, int tailleEnPix,int nb_case)
{
    int randomY, randomX;
    //on attribue à chaque case Rail courbe un point aleatoire
    do{
        randomX = qrand() % nb_case-1;
        randomY = qrand() % nb_case-1;
    }(while(matrice_case->contains(QPoint(randomX,randomY))));

}*/

void Grille::afficher(QPainter *p)
{
    for (int i = 0; i<nb_case; ++i)
    {
        for (int j = 0; j<nb_case; ++j)
        {
            matrice_case[i][j]->afficher(p);
        }
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
    QPoint posCourante(0,0);
    QPoint posPreced(0,0);
    Case *caseCourante = matrice_case[posCourante.y()][posCourante.x()];

    QString retour, instructionDeplacement="";
    QChar deplacement;

    int k = 0;
    bool connection = false;

    // Si la première case de la matrice n'est pas d'un type de case
    // qui pointe vers le bord gauche de la grille alors le chemin
    // est faux
    if (!(caseCourante->getType()==1 || caseCourante->getType()==5))
    {
        return "0";
    }

    while(continuer)
    {
        std::vector<QPoint> vois = PosVoisine(posCourante);
        k = 0;
        connection = false;
        while (!connection && k < (int)vois.size())
        {
            Case *suivante = matrice_case[vois[k].y()][vois[k].x()];

            deplacement = sontConnecter(posCourante, vois[k]);
            if (vois[k]!=posPreced && deplacement!='0')
            {
                posPreced = posCourante;
                caseCourante = suivante;
                posCourante = vois[k];
                connection = true;
                instructionDeplacement += deplacement;
            }
            k++;
        }
        if (!connection)
            continuer = false;
    }

    // On verifie si la dernière case valide est la case de sortie
    // On verifie aussi si elle pointe dans la bonne direction
    if (posCourante==QPoint(nb_case-1, nb_case-1) && (caseCourante->getType()==1 || caseCourante->getType()==3))
    {
        return "1"+instructionDeplacement;
    }
    else
    {
        return "0"+instructionDeplacement;
    }
}

std::vector<QPoint> Grille::PosVoisine(QPoint pos)
{
    std::vector<QPoint> vois;
    if (pos.x() > 0)
        vois.push_back(QPoint(pos.x()-1, pos.y()));

    if (pos.x() < nb_case-1)
        vois.push_back(QPoint(pos.x()+1, pos.y()));

    if (pos.y() < nb_case-1)
        vois.push_back(QPoint(pos.x(), pos.y()+1));

    if (pos.y() > 0)
        vois.push_back(QPoint(pos.x(), pos.y()-1));

    return vois;
}

// le sens est important
// cette fonction retourne la direction de déplacement entre 2 cases adjacente
// et '0' si le déplacement n'est pas possible
QChar Grille::sontConnecter(QPoint posCour, QPoint posSuiv)
{
    Case *suiv = matrice_case[posSuiv.y()][posSuiv.x()];
    Case *cour = matrice_case[posCour.y()][posCour.x()];
    bool dir, courValide, suivValide;

    // Une case ne peut pas etre connecter à la case vide
    if (suiv->getType()==0)
        return '0';

    // Si  la case d'arrivé est à gauche de la case de départ
    dir = (posCour.x()==posSuiv.x()+1);
    courValide = (cour->getType()==1 || cour->getType()==5 || cour->getType()==6);
    suivValide = (suiv->getType()==1 || suiv->getType() ==3 || suiv->getType()==4);
    if (dir && courValide && suivValide)
        return 'g';


    // Si  la case d'arrivé est à droite de la case de départ
    dir = (posCour.x()==posSuiv.x()-1);
    courValide = (cour->getType()==1 || cour->getType()==3 || cour->getType()==4);
    suivValide = (suiv->getType()==1 || suiv->getType() ==5 || suiv->getType()==6);
    if (dir && courValide && suivValide)
        return 'd';

    // Si  la case d'arrivé est en haut de la case de départ
    dir = (posCour.y()==posSuiv.y()+1);
    courValide = (cour->getType()==2 || cour->getType()==3 || cour->getType()==6);
    suivValide = (suiv->getType()==2 || suiv->getType() ==4 || suiv->getType()==5);
    if (dir && courValide && suivValide)
        return 'h';

    // Si  la case d'arrivé est en bas de la case de départ
    dir = (posCour.y()==posSuiv.y()-1);
    courValide = (cour->getType()==2 || cour->getType()==4 || cour->getType()==5);
    suivValide = (suiv->getType()==2 || suiv->getType() ==3 || suiv->getType()==6);
    if (dir && courValide && suivValide)
        return 'b';

    return '0';
}

void Grille::deplacer(Case &c)
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

    // (i,j) coordonné de la case vide dans la matrice
    Case *caseVide = matrice_case[i][j];

    // Permet d'échanger les coordonnée dans le repere graphique des 2 cases
    c.echanger(*caseVide);

    // Il faut aussi échanger les positions des deux cases dans la matrice

    // Il faut d'abord trouver les coordonee de la case c
    int x=0, y=0;
    while((y<nb_case)&&((matrice_case[y][x])!=&c)){
        //on parcours ligne par ligne la matrice des cases
        if(x<nb_case-1) x++;
        else{
            //on passe  à la ligne suivante
            x=0;
            y++;
        }
    }

    // echange des cases dans la matrice
    matrice_case[i][j] = &c;
    matrice_case[y][x] = caseVide;
}

//getters et setters
int Grille::getNbCase(){
    return nb_case;
}
Case*** Grille::getMatrice(){
    return matrice_case;
}
QPoint Grille::getPos(){
    return pos;
}
