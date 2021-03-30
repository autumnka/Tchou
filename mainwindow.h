#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QRadioButton>
#include <QDebug>
#include <chrono>
#include <thread>
#include <QRect>

#include "ui_mainwindow.h"
#include "aide.h"
#include "ui_aide.h"
#include"resultat.h"
#include "ui_resultat.h"
#include "grille.h"
#include "feu.h"
#include "train.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void switchAffichage();

    void afficherTchou(QPainter* painter) const;
    void afficherFleche(QPainter* painter) const;

    void affichePartie();
    void afficherGrille();

    void afficherFeu();

    void AllumerFeu();

    void afficherTrain();

    void deplacerCase(QMouseEvent *me);

    void roulerTrain(QString direction, int v);

    void afficherResultat(int g);

    void placerTrainDepart();

private slots:
    void on_button_aide_clicked();
    void button_jouer_clicked();
    void mousePressEvent(QMouseEvent *me);
    //void mouseMoveEvent(QMouseEvent *event);
    void selectionnerNiv1();
    void selectionnerNiv2();
    void selectionnerVit1();
    void selectionnerVit2();
    void selectionnerVit3();


    void on_buttonDemarrerTrain_clicked();

    void on_Retour_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* e);

    void setUpParametreWindow();
    QWidget **list_widget_parametre_window;

    QString interfaceCourante; // soit "parametre", soit "partie"

    int vitesseTrain=1;
    int tailleGrille=2; // Le nombre de case de la grille
    int taillePixelGrille=500;
    //coordonnee du coin en haut a gauche
    QPoint *posGrille = new QPoint(150,50);
    Grille *grille;

    Feu* feu;
    Train *train;
};
#endif // MAINWINDOW_H
