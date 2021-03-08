#ifndef CASEVIDE_H
#define CASEVIDE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "case.h"

class CaseVide : public Case
{
    public:
        CaseVide(int type, QPoint p, int taille);
        void afficher(QPainter *painter) const;
};

#endif // CASEVIDE_H
