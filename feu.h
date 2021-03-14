#ifndef FEU_H
#define FEU_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>

class Feu
{
public:
    Feu();
    Feu(QPoint position, int etat=0);
    int getEtat();

    void allumer(bool chemin);
    void eteindre();
    void afficher(QPainter *painter) const;
private:
    QPoint *m_position=new QPoint(670,50);
    int m_etatFeu=0;
    //0: eteint
    //1: vert
    //2: rouge
};

#endif // FEU_H
