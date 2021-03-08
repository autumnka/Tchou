#ifndef CASE_H
#define CASE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Case
{
    public:
        Case(int type, QPoint p, int taille);
        QPoint getPosition() const;
        void setPosition(QPoint p);
        int getType();
        void setType(int type);

        void echanger(Case &c);
        virtual void afficher(QPainter *painter) const = 0;

    protected:
        QPoint m_p;
        int m_typeCase;
        int m_taille;
};

#endif // CASE_H
