#ifndef CASERAIL_H
#define CASERAIL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "case.h"

//enum Direction {h, b, g, d};

class CaseRail : public Case
{
    public:
        CaseRail(int type, QPoint p={0, 0}, int taille=1);
        void afficher(QPainter *painter) const;

    private:

};

#endif // CASERAIL_H
