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

void Train::rouler(char direction){
    QPoint p=getPosition();
    switch(direction){
        case 'h':p.ry()--;
        break;
        case 'b':p.ry()++;
        break;
        case 'g':p.rx()--;
        break;
        case 'd':p.rx()++;
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
