#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QRadioButton>

#include "ui_mainwindow.h"
#include "aide.h"
#include "ui_aide.h"
#include "partie.h"
#include "grille.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void changerAffichage();

    void selectionnerNiv1();
    void selectionnerNiv2();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* e);

    // Ci dessous les fonctions qui servent à l'affiche de la partie ou des paramètres
    void affichePartie();
    // Vaut 0 si la MainWindow affiche les parametre et vaux 1 si elle affiche la partie
    bool affichage;
    void setUpParametreWindow();
    QWidget **list_widget_parametre_window;

    int m_niv = -1;

    void afficherGrille();
};
#endif // MAINWINDOW_H
