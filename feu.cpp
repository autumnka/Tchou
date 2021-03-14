#include "feu.h"

Feu::Feu()
{

}
Feu::Feu(QPoint position, int etat)
{
    m_position=new QPoint(position);
    m_etatFeu=etat;
}

int Feu::getEtat(){
    return m_etatFeu;
}

//on allume le feu selon que le chemin soit bon ou pas
void Feu::allumer(bool chemin){
    if(chemin){
        m_etatFeu=1; //Feu vert
    }
    else m_etatFeu=2; //Feu rouge

}
//on eteint le feu
void Feu::eteindre(){
    m_etatFeu=0;
}

// cette fonction se declenche après l'evenement appuyerFeu
//on allume le feu en fonction de son etat
void Feu:: afficher(QPainter *painter) const{
    QPixmap *pixmap;
    switch (m_etatFeu) {
        case 0:pixmap = new QPixmap(":/images/feuEteint.jpg");
            break;
        case 1:pixmap = new QPixmap(":/images/feuVert.jpg");
        break;
        case 2:pixmap = new QPixmap(":/images/feuRouge.jpg");
        break;

    }
     painter->drawPixmap(m_position->x(), m_position->y(), 90, 200,*pixmap);
}

