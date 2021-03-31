#include "casevide.h"
///
/// \fn CaseVide::CaseVide(int type, QPoint p, int taille) : Case(0, p, taille)
/// \brief CaseVide::CaseVide
/// \param type: type de la case
/// \param p: coordonnees de la case
/// \param taille: taille de la case
///
CaseVide::CaseVide(int type, QPoint p, int taille) : Case(0, p, taille)
{

}
///
/// \fn CaseVide::afficher(QPainter *painter) const
/// \brief CaseVide::afficher
/// \param painter: QPainter*
///
void CaseVide::afficher(QPainter *painter) const
{
     QPixmap *pixmap;
     pixmap = new QPixmap(":/images/Vide.jpg");
     painter->drawPixmap(m_p.x(), m_p.y(), m_taille, m_taille, *pixmap);
}
