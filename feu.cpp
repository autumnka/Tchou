#include "feu.h"

Feu::Feu(QPoint position, int etat)
{
    m_position=position;
    m_etatFeu=etat;
}
//on allume le feu selon que le chemin soit bon ou pas
void Feu::allumer(bool chemin){
    if(chemin){
        m_etatFeu=1; //Feu vert
    }
    else m_etatFeu=2; //Feu rouge

}
//on eteint le feu
void Feu::eteindre(){
    m_etatFeu=0;
}
