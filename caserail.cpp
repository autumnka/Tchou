#include "caserail.h"

CaseRail::CaseRail(int type, QPoint p, int taille) : Case(type, p,taille)
{
   // m_bout1 = bout1;
   // m_bout2 = bout2;
}

void CaseRail:: afficher(QPainter *painter) const{
    QPixmap *pixmap;
    switch (m_typeCase)
    {
        case 1: pixmap = new QPixmap(":/images/rail_horizontal.png");
            break;
        case 2: pixmap = new QPixmap(":/images/rail_vertical.png");
            break;
        case 3: pixmap = new QPixmap(":/images/rail_courbe1.jpg");
            break;
        case 4: pixmap = new QPixmap(":/images/rail_courbe3.jpg");
            break;
        case 5: pixmap = new QPixmap(":/images/rail_courbe4.jpg");
            break;
        case 6: pixmap = new QPixmap(":/images/rail_courbe2.jpg");
    }

    painter->drawPixmap(m_p.x(), m_p.y(), m_taille, m_taille, *pixmap);
}
