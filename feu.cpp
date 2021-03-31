#include "feu.h"
///
/// \fn Feu::Feu()
/// \brief Constructeur de Feu par defaut
///
Feu::Feu()
{

}
///
/// \fn Feu::Feu(QPoint position, int etat)
/// \brief Constructeur de recopie de feu
/// \param position: coordonnées du feu
/// \param etat: etat du feu (0:eteint, 1:vert, 2:rouge)
///
Feu::Feu(QPoint position, int etat)
{
    m_position=new QPoint(position);
    m_etatFeu=etat;
}
///
/// \fn Feu::getEtat()
/// \brief Feu::getEtat
/// \return etat du feu
///
int Feu::getEtat(){
    return m_etatFeu;
}

///
/// \fn Feu::allumer(bool chemin)
/// \brief Feu::allumer
/// \details allume le feu selon que le chemin soit bon ou pas
/// \param chemin:1 si le chemin est valide, 0 sinon
///
void Feu::allumer(bool chemin){
    if(chemin){
        m_etatFeu=1; //Feu vert
    }
    else m_etatFeu=2; //Feu rouge

}

///
/// \fn Feu::eteindre()
/// \detail eteint le feu
/// \brief Feu::eteindre
///
void Feu::eteindre(){
    m_etatFeu=0;
}

///
/// \fn Feu:: afficher(QPainter *painter) const
/// \brief Feu::afficher
/// \details affiche le feu en fonction de son etat
/// \details cette fonction se declenche après l'evenement appuyerFeu
/// \param painter: QPainter*
///
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

