#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aide.h"
#include "ui_aide.h"
#include <QtGui>
#include <QRadioButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setUpParametreWindow();

    interfaceCourante = "parametre";

    grille = new Grille();
    feu = new Feu();
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

    QObject::connect(jouer, SIGNAL(clicked()), this, SLOT(button_jouer_clicked()));

    QObject::connect(niv1, SIGNAL(clicked()), this, SLOT(selectionnerNiv1()));
    QObject::connect(niv2, SIGNAL(clicked()), this, SLOT(selectionnerNiv2()));
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

    switchAffichage();
}

void MainWindow::switchAffichage()
{
    interfaceCourante = "partie";
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    affichePartie();

    if (interfaceCourante == "partie")
        afficherFeu();
}

void MainWindow::afficherFeu()
{
    QPainter *painter = new QPainter(this);
    feu->afficher(painter);
    delete painter;
}

void MainWindow::affichePartie()
{
    bool interfac=true;
    if (interfaceCourante =="parametre")
        interfac = true;
    else
    {
        interfac = false;
        afficherGrille();
    }
    ui->centralwidget->setVisible(!interfac);
    for (int i=0; i<4; i++)
        this->list_widget_parametre_window[i]->setVisible(interfac);
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

void MainWindow::afficherGrille()
{
    QPainter *painter = new QPainter(this);
    grille->afficher(painter);
    delete painter;
}

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
//on appuie sur le bouton pour lancer le train normalement
//mais pour l'instant c'est juste pour allumer le feu
/*void MainWindow::on_AppuyerFeu_clicked()
{
    QPainter *painter = new QPainter(this);
    //on verifie le chemin
    //bool valide=(grille->verifierChemin()[0]).digitValue();
    //on change l'etat du feu
    //feu->allumer(valide);
    //on allume le feu de la bonne couleur
    //feu->afficher(painter);
    //repaint();
}
*/

/*void MainWindow::on_AppuyerFeu_clicked()
{
    QPainter *painter = new QPainter(this);
    //on verifie le chemin
    //bool valide=(grille->verifierChemin()[0]).digitValue();
    //on change l'etat du feu
    //feu->allumer(valide);
    //on allume le feu de la bonne couleur
    //feu->afficher(painter);
    //repaint();
}*/

void MainWindow::on_buttonDemarrerTrain_clicked()
{
    QString s = grille->verifierChemin();
    qDebug() << s;
    bool valide = (s[0]=='1');

    qDebug() << valide;
    feu->allumer(valide);
    repaint();

    /*feu->allumer(true);
    repaint();*/
}
