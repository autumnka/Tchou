#include "train.h"

Train::Train()
{

}

Train::Train(QPoint position, QPoint taille)
{
    m_position=position;
    taillePixel = taille;
}

void Train::afficher(QPainter *painter)
{
    QPixmap *pixmap = new QPixmap(":/images/train.jpeg");
    painter->drawPixmap(m_position.x(), m_position.y(), taillePixel.x(), taillePixel.y(), *pixmap);
    //painter->drawPixmap(m_position.x(), m_position.y(), 100, 100, *pixmap);
    delete pixmap;
}
//on rajoute le pas en parametre
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

QPoint Train::getPosition(){
    return m_position;
}
void Train::setPosition(QPoint a){
    m_position=a;
}

QPoint Train::getTaillePix()
{
    return taillePixel;
}

void Train::setTaillePix(QPoint t)
{
    taillePixel = t;
}
