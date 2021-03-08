#ifndef CASERAIL_H
#define CASERAIL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "case.h"
#include <QtGui>

class CaseRail : public Case
{
    public:
        CaseRail(int type, QPoint p, int taille);

        void afficher(QPainter *painter) const;
};

#endif // CASERAIL_H
