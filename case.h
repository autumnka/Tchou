///
/// \file case.h
/// \brief La classe Case permet de manipuler des cases
/// \author PAULINEAU Jules,POUILLOT Samuel
/// \version 1.0
/// \date 31/03/2021
///
#ifndef CASE_H
#define CASE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>

class Case
{
    public:
        Case(int type=0, QPoint p = {0, 0},int taille=1);
        QPoint getPosition() const;
        void setPosition(QPoint p);
        int getType() const;
        void setType(int type);
        int getTaille() const;
        void setTaille(int taille);

        void echanger(Case &c);
        virtual void afficher(QPainter *painter) const = 0;

    protected:
        // position en pixel
        QPoint m_p;
        int m_typeCase;
        int m_taille;
};

#endif // CASE_H
