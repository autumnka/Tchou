#include "case.h"

Case::Case(int type, QPoint p,int taille)
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

int Case::getType() const{
    return m_typeCase;
}

void Case::setType(int type){
    m_typeCase = type;
}
int Case::getTaille() const{
    return m_taille;
}

void Case::setTaille(int taille){
    m_taille = taille;
}
void Case::echanger(Case &c)
{
    QPoint tempo = m_p;

    m_p = c.m_p;
    c.setPosition(tempo);
}

//appelle la fonction afficher des sous classes
//void Case::afficher(){}
