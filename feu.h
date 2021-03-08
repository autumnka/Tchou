#ifndef FEU_H
#define FEU_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Feu
{
public:
    Feu(QPoint position, int etat=0);
    //void afficher();
    void allumer(bool chemin);
    void eteindre();
private:
    QPoint m_position;
    int m_etatFeu;
    //0: eteint
    //1: vert
    //2: rouge
};

#endif // FEU_H
