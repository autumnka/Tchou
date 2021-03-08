#include "train.h"

Train::Train(QPoint position){
    m_position=position;
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
//a faire au moment de l'interface graphique
/*void Train::afficher(){
}*/
QPoint Train::getPosition(){
    return m_position;
}
void Train::setPosition(QPoint a){
    m_position=a;
}
