#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aide.h"
#include "ui_aide.h"
#include <QtGui>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setUpParametreWindow();

    affichage = false;
    //this->affichePartie();
}

// Créer les widgets pour quand la MainWindow est en mode paramatre
void MainWindow::setUpParametreWindow()
{
    list_widget_parametre_window = new QWidget*[4];

    QPushButton *jouer = new QPushButton("jouer ! ", this);
    jouer->move(600, 500);

    QLabel *niv = new QLabel("Choisir le niveau ", this);
    niv->move(100, 300);
    niv->setFixedWidth(200);

    QRadioButton *niv1 = new QRadioButton("Facile", this);
    QRadioButton *niv2 = new QRadioButton("Difficile", this);
    niv1->move(100, 400);
    niv2->move(300, 400);

    list_widget_parametre_window[0] = jouer;
    list_widget_parametre_window[1] = niv;
    list_widget_parametre_window[2] = niv1;
    list_widget_parametre_window[3] = niv2;

    QObject::connect(jouer, SIGNAL(clicked()), this, SLOT(changerAffichage()));

    QObject::connect(niv1, SIGNAL(clicked()), this, SLOT(selectionnerNiv1()));
    QObject::connect(niv2, SIGNAL(clicked()), this, SLOT(selectionnerNiv2()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Aide a(this);
    a.exec();
}

void MainWindow::changerAffichage()
{
    affichage = !affichage;
    affichePartie();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    affichePartie();
}

void MainWindow::affichePartie()
{
    ui->centralwidget->setVisible(affichage);

    for (int i=0; i<4; i++)
        this->list_widget_parametre_window[i]->setVisible(!affichage);
    if (affichage)
        afficherGrille();
}

void MainWindow::selectionnerNiv1()
{
    ui->label_4->setText("Partie de TchouTchou niveau facile");
    m_niv = 1;
}

void MainWindow::selectionnerNiv2()
{
    ui->label_4->setText("Partie de TchouTchou niveau difficile");
    m_niv=2;
}
void MainWindow::afficherGrille()
{
    QPainter *painter = new QPainter(this);

    //int x = 150, y = 50, taille = 500;

    int taille_grille;
    if (m_niv == 1)
        taille_grille = 2;
    else
        taille_grille = 3;

    Grille *g=new Grille(QPoint(150,50), 500, QPoint(0,0), QPoint(0, 0), taille_grille);
    g->afficher(painter);
}

void MainWindow::zoneClick(){


}


