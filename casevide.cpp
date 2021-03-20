#include "casevide.h"

CaseVide::CaseVide(int type, QPoint p, int taille) : Case(0, p, taille)
{

}
void CaseVide::afficher(QPainter *painter) const
{
     QPixmap *pixmap;
     pixmap = new QPixmap(":/images/Vide.jpg");
     painter->drawPixmap(m_p.x(), m_p.y(), m_taille, m_taille, *pixmap);
}
