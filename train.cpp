#include "train.h"
///
/// \fn Train::Train()
/// \brief constructeur par defaut de train
///
Train::Train()
{

}
///
/// \fn Train::Train(QPoint position, QPoint taille)
/// \brief Train::Train
/// \param position: coordonnees du train
/// \param taille: taille du train
///
Train::Train(QPoint position, QPoint taille)
{
    m_position=position;
    taillePixel = taille;
}
///
/// \fn Train::afficher(QPainter *painter)
/// \brief Train::afficher
/// \param painter: QPainter*
///
void Train::afficher(QPainter *painter)
{
    QPixmap *pixmap = new QPixmap(":/images/train.png");
    painter->drawPixmap(m_position.x(), m_position.y(), taillePixel.x(), taillePixel.y(), *pixmap);
    //painter->drawPixmap(m_position.x(), m_position.y(), 100, 100, *pixmap);
    delete pixmap;
}
//on rajoute le pas en parametre
///
/// \fn Train::rouler(QChar direction, int pas)
/// \brief Train::rouler
/// \param direction:direction dans laquelle le train va rouler(haut:'h',bas:'b',droite:'d'ou gauche:'g')
/// \param pas: taille du pas de deplacement du train
///
void Train::rouler(QChar direction, int pas){
    QPoint p=getPosition();
    switch(direction.unicode()){
        case 'h':p.setY(p.y()-pas);
        break;
        case 'b':p.setY(p.y()+pas);
        break;
        case 'g':p.setX(p.x()-pas);
        break;
        case 'd':p.setX(p.x()+pas);
        break;
    }
    this->setPosition(p);
}
///
/// \fn Train::getPosition()
/// \brief Train::getPosition
/// \return la position du train
///
QPoint Train::getPosition(){
    return m_position;
}
///
/// \fn Train::setPosition(QPoint a)
/// \brief Train::setPosition
/// \param a: nouvelle position du train
///
void Train::setPosition(QPoint a){
    m_position=a;
}
///
/// \fn Train::getTaillePix()
/// \brief Train::getTaillePix
/// \return la taille en pixel du train
///
QPoint Train::getTaillePix()
{
    return taillePixel;
}
///
/// \fn Train::setTaillePix(QPoint t)
/// \brief Train::setTaillePix
/// \param t: nouvelle taille en pixel du train
///
void Train::setTaillePix(QPoint t)
{
    taillePixel = t;
}
