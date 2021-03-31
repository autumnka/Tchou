#include "caserail.h"
///
/// \fn CaseRail::CaseRail(int type, QPoint p, int taille) : Case(type, p,taille)
/// \brief constructeur de CaseRail
/// \param type: type de rail
/// \param p: coordonnees de la cases
/// \param taille: taille de la case
///
CaseRail::CaseRail(int type, QPoint p, int taille) : Case(type, p,taille)
{
   // m_bout1 = bout1;
   // m_bout2 = bout2;
}
///
/// \fn CaseRail:: afficher(QPainter *painter) const
/// \brief CaseRail::afficher
/// \details on affiche une image differente selon le type de rail
/// \param painter: QPainter*
///
void CaseRail:: afficher(QPainter *painter) const{
    QPixmap *pixmap;
    switch (m_typeCase)
    {
        case 1: pixmap = new QPixmap(":/images/RailHorizontale.jpg");
            break;
        case 2: pixmap = new QPixmap(":/images/RailVerticale.jpg");
            break;
        case 3: pixmap = new QPixmap(":/images/RailCourbeHD.jpg");
            break;
        case 4: pixmap = new QPixmap(":/images/RailCourbeBD.jpg");
            break;
        case 5: pixmap = new QPixmap(":/images/RailCourbeGB.jpg");
            break;
        case 6: pixmap = new QPixmap(":/images/RailCourbeGH.jpg");
    }

    painter->drawPixmap(m_p.x(), m_p.y(), m_taille, m_taille, *pixmap);
}
