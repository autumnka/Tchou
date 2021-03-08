#include "case.h"

Case::Case(int type, QPoint p, int taille)
{
    m_p = p;
    m_typeCase = type;
    m_taille = taille;
}

QPoint Case::getPosition() const
{
    return m_p;
}

void Case::setPosition(QPoint p)
{
    m_p = p;
}

int Case::getType()
{
    return m_typeCase;
}

void Case::setType(int type)
{
    m_typeCase = type;
}

void Case::echanger(Case &c)
{
    QPoint tempo = m_p;

    m_p = c.m_p;
    c.m_p = tempo;
}
