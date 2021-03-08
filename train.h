#ifndef TRAIN_H
#define TRAIN_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Train
{
    public:
        Train(QPoint position);
        void rouler(char direction);
        //void afficher();
        QPoint getPosition();
        void setPosition(QPoint a);

    private:
        QPoint m_position;
};

#endif // TRAIN_H
