#include "case.h"
///
/// \fn Case::Case(int type, QPoint p,int taille)
/// \brief constructeur de Case
/// \param type:
/// \param p:
/// \param taille: taille de la case en
///
Case::Case(int type, QPoint p,int taille)
{
    m_p = p;
    m_typeCase = type;
    m_taille = taille;
}
///
/// \fn Case::getPosition() const
/// \brief Case::getPosition
/// \return la position de la case
///
QPoint Case::getPosition() const
{
    return m_p;
}
///
/// \fn Case::setPosition(QPoint p)
/// \brief Case::setPosition
/// \param p: nouvelle position de la case
///
void Case::setPosition(QPoint p)
{
    m_p = p;
}
///
/// \fn Case::getType() const
/// \brief Case::getType
/// \return le type de la case
///
int Case::getType() const{
    return m_typeCase;
}
///
/// \fn Case::setType(int type)
/// \brief Case::setType
/// \param type: nouveau type de la case
///
void Case::setType(int type){
    m_typeCase = type;
}
///
/// \fn Case::getTaille() const
/// \brief Case::getTaille
/// \return taille de la case
///
int Case::getTaille() const{
    return m_taille;
}
///
/// \fn Case::setTaille(int taille)
/// \brief Case::setTaille
/// \param taille: nouvelle taille de la case
///
void Case::setTaille(int taille){
    m_taille = taille;
}
///
/// \fn Case::echanger(Case &c)
/// \brief Case::echanger
/// \param c: reference de la Case a echanger avec la case courante
///
void Case::echanger(Case &c)
{
    QPoint tempo = m_p;

    m_p = c.m_p;
    c.setPosition(tempo);
}
