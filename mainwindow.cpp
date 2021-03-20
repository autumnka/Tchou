#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aide.h"
#include "ui_aide.h"
#include "resultat.h"
#include "ui_resultat.h"
#include <QtGui>
#include <QRadioButton>
#include <QDebug>
#include <QTimer>
#include <chrono>
#include <thread>
#include <QRect>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setUpParametreWindow();

    interfaceCourante = "parametre";

    grille = new Grille();
    feu = new Feu();
    train = new Train();
}

// Créer les widgets pour quand la MainWindow est en mode paramatre
void MainWindow::setUpParametreWindow()
{
    list_widget_parametre_window = new QWidget*[4];
    //g1=new QGroupBox[4];
    QPushButton *jouer = new QPushButton("jouer ! ", this);
    jouer->move(600, 500);

    QLabel *niv = new QLabel("Choisir le niveau ", this);
    niv->move(100, 350);
    niv->setFixedWidth(200);

    QRadioButton *niv1 = new QRadioButton("Facile", this);
    QRadioButton *niv2 = new QRadioButton("Difficile", this);
    niv1->move(100, 400);
    niv2->move(300, 400);

    list_widget_parametre_window[0] = jouer;
    list_widget_parametre_window[1] = niv;
    list_widget_parametre_window[2] = niv1;
    list_widget_parametre_window[3] = niv2;

    list_widget_parametre_vitesse = new QWidget*[4];
    //g2=new QGroupBox[4];
    QLabel *vitesse = new QLabel("Choisir la vitesse du train ", this);
    vitesse->move(100, 450);
    vitesse->setFixedWidth(200);
    QRadioButton *vitesse1 = new QRadioButton("Lent", this);
    QRadioButton *vitesse2= new QRadioButton("Modéré", this);
    QRadioButton *vitesse3 = new QRadioButton("Rapide", this);
    vitesse1->move(100, 500);
    vitesse2->move(200, 500);
    vitesse3->move(300, 500);

    list_widget_parametre_vitesse[0] = vitesse;
    list_widget_parametre_vitesse[1] = vitesse1;
    list_widget_parametre_vitesse[2] = vitesse2;
    list_widget_parametre_vitesse[3] = vitesse3;

    QObject::connect(jouer, SIGNAL(clicked()), this, SLOT(button_jouer_clicked()));
    QObject::connect(niv1, SIGNAL(clicked()), this, SLOT(selectionnerNiv1()));
    QObject::connect(niv2, SIGNAL(clicked()), this, SLOT(selectionnerNiv2()));

    QObject::connect(vitesse1, SIGNAL(clicked()), this, SLOT(selectionnerVit1()));
    QObject::connect(vitesse2, SIGNAL(clicked()), this, SLOT(selectionnerVit2()));
    QObject::connect(vitesse3, SIGNAL(clicked()), this, SLOT(selectionnerVit3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_aide_clicked()
{
    Aide a(this);
    a.exec();
}

void MainWindow::button_jouer_clicked()
{
    grille = new Grille(*posGrille, taillePixelGrille, tailleGrille);

    // la taille du train = 0.6 fois taille d'une case
    int tPixTrain = 0.6*taillePixelGrille/tailleGrille;

    // permet de centrer en y la train par rapport au case
    int yTrain = (taillePixelGrille/tailleGrille - tPixTrain)/2 + posGrille->y();
    // permet de placer le train juste au bord
    int xTrain = posGrille->x()-tPixTrain;

    train = new Train(QPoint(xTrain,yTrain), QPoint(tPixTrain, tPixTrain));

    switchAffichage();
}

void MainWindow::switchAffichage()
{
    if (interfaceCourante == "parametre")
        interfaceCourante = "partie";
    else
        interfaceCourante = "parametre";
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    affichePartie();

    if (interfaceCourante == "partie")
    {
        afficherFeu();
        afficherTrain();
    }
}
//affiche l'image principale sur l'interface de Configuration
void MainWindow::afficherTchou(QPainter *painter) const{
    QPixmap *pixmap= new QPixmap(":/images/petitTrain.jpg");
    painter->drawPixmap(200,30, 450, 300,*pixmap);
}

void MainWindow::afficherFeu()
{
    QPainter *painter = new QPainter(this);
    feu->afficher(painter);
    delete painter;
}

void MainWindow::afficherTrain()
{
    QPainter *painter = new QPainter(this);
    train->afficher(painter);
    delete painter;
}

void MainWindow::affichePartie()
{
    QPainter *painter = new QPainter(this);
    bool interfac=true;
    if (interfaceCourante =="parametre"){
        interfac = true;
        afficherTchou(painter);
    }
    else
    {
        interfac = false;
        afficherGrille();
    }
    ui->centralwidget->setVisible(!interfac);
    for (int i=0; i<4; i++){
        this->list_widget_parametre_window[i]->setVisible(interfac);
        this->list_widget_parametre_vitesse[i]->setVisible(interfac);
    }
     delete painter;
}

void MainWindow::selectionnerNiv1()
{
    ui->label_4->setText("Partie de TchouTchou niveau facile");
    tailleGrille = 2;
}

void MainWindow::selectionnerNiv2()
{
    ui->label_4->setText("Partie de TchouTchou niveau difficile");
    tailleGrille = 3;
}

void MainWindow::selectionnerVit1()
{
    vitesseTrain = 1;
}
void MainWindow::selectionnerVit2()
{
    vitesseTrain = 2;
}
void MainWindow::selectionnerVit3()
{
    vitesseTrain = 4;
}

void MainWindow::afficherGrille()
{
    QPainter *painter = new QPainter(this);
    grille->afficher(painter);
    delete painter;
}
//pour mettre en surbrillance la case sur laquelle on passe
/*void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint p=event->pos();
    QPainter *painter;
    for(int i=0;i<grille->getNbCase();i++)
    {
        for(int j=0;j<grille->getNbCase();j++)
        {
            Case *c=grille->getMatrice()[i][j];
            int x = c->getPosition().x();
            int y = c->getPosition().y();
            if (p.x()>=x && p.x()<=x+c->getTaille() && p.y()>=y && p.y()<=y+c->getTaille()){
                QRect rectangle(x,y,c->getTaille(),c->getTaille());
                QMargins m(10,10,10,10);
                rectangle.marginsAdded(m);
                painter->drawRoundedRect(rectangle,10,10);
            }
        }
    }
    repaint();
}*/

void MainWindow::mousePressEvent(QMouseEvent *me)
{
    if (interfaceCourante == "partie")
        deplacerCase(me);
}

void MainWindow::deplacerCase(QMouseEvent *me)
{
    QPoint p=me->pos();

    //on recupere la position du click de la souris
    if(me->button()==Qt::LeftButton)
    {
            for(int i=0;i<grille->getNbCase();i++)
            {
                for(int j=0;j<grille->getNbCase();j++)
                {
                    Case *c = grille->getMatrice()[i][j];
                    int x = c->getPosition().x();
                    int y = c->getPosition().y();
                    if (p.x()>=x && p.x()<=x+c->getTaille() && p.y()>=y && p.y()<=y+c->getTaille())
                        grille->deplacer(*c);
                }
            }
    }
    repaint();
}

void MainWindow::on_buttonDemarrerTrain_clicked()
{
    QString s = grille->verifierChemin();
    qDebug() << s;

    bool valide = (s[0]=='1');
    feu->allumer(valide);
    repaint();
    roulerTrain(s,vitesseTrain);
}

void MainWindow::roulerTrain(QString direction, int v)
{
    // taille d'une case
    int tPixCase = taillePixelGrille/tailleGrille;
    // taille en pixel du train
    int tPixTrain = train->getTaillePix().x();
    // permet de centrer en y la train par rapport au case
    int yTrain = (tPixCase - tPixTrain)/2 + posGrille->y();
    // permet de centrer en y la train par rapport au case
    int xTrain = (tPixCase - tPixTrain)/2 + posGrille->x();
    // Si le train peut aller sur la première case on le met au milieu dessus

    int k=0;
    //int courbe=0;
    int inter=20; //nombre de subdivision du pas du train
    if (direction.size() > 1){
        train->setPosition(QPoint(xTrain, yTrain));
        repaint();
    }
    //on fait bouger le train case par case
    for (int i = 1; i < direction.size(); ++i)
    {
        //pour toutes cases, on commence par avancer dans la direction indiquee
        for (int j = 1; j < 3*inter/4; ++j)
        {
            //on fait une pause entre chaque deplcement du train
            this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
            train->rouler(direction[i],tPixCase/inter);
            repaint();
        }
        //on continue si on suit la meme direction que precedemment

        if(i<direction.size()-1){
            qDebug() << "test direction"<<i;
            if(direction[i]==direction[i+1]){
                qDebug() << "rail droit";
                for (int j = 3*inter/4; j < inter; ++j)
                {
                this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                train->rouler(direction[i],tPixCase/inter);
                repaint();
                }
            }
            //on va effectuer une trajectoire courbe pour epouser la forme du rail
            else{
                 qDebug() << "rail courbe("<<direction[i]<<","<<direction[i+1]<<")";
                for (int j = 3*inter/4; j < inter; ++j)
                {
                    this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                    //on calcule le prochain point pour approximer une courbe
                    k=1+j-3*inter/4;
                    //courbe=acos(1-sin(j*tPixCase/(2*inter)));

                    //on se déplace selon l'axe de la premiere direction
                    //train->rouler(direction[i],tPixCase/(2*inter*k));
                    train->rouler(direction[i],tPixCase/(2*inter));
                    //on se deplace dans l'axe de la 2 eme direction
                   // train->rouler(direction[i+1],k*tPixCase/(2*inter));//on anticipe le futur déplacemnt
                    train->rouler(direction[i+1],tPixCase/(2*inter));
                    repaint();
                     qDebug() << k;
                }
            }
        }
    }
    //si le chemin est valide on deplace le train un cran de plus
    if (direction[0]=='1')
    {
         qDebug() << "on sort";
        for (int j = 1; j < inter; ++j)
        {
            qDebug() << j;
            this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
            train->rouler('d',tPixCase/inter);
            repaint();
        }

    }
    afficherResultat(direction[0].unicode());
}

void MainWindow::on_Retour_clicked()
{
    switchAffichage();
}

void MainWindow::afficherResultat(int g){
    //on teste si le joueur a gagné
    Resultat r(this);
    if(g==1){
        r.exec();//pour l'instant ça affiche juste la même fenêtre que si Perdu
        qDebug() << "TU GAGNES!!!";
    }
    else{
        r.exec();
        qDebug() << "TU A PERDU!!!";
    }
}
