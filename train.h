#ifndef TRAIN_H
#define TRAIN_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPainter>
//#include <QChar>

class Train
{
    public:
        Train();
        Train(QPoint position, QPoint taille);
        void rouler(QChar direction, int pas);
        void afficher(QPainter *painter);
        QPoint getPosition();
        void setPosition(QPoint a);
        QPoint getTaillePix();
        void setTaillePix(QPoint t);

    private:
        QPoint m_position;
        QPoint taillePixel;
};

#endif // TRAIN_H
