#include "mainwindow.h"

using namespace std;
///
/// \fn MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
/// \brief constructeur de Mainwindow
/// \param parent: QWidget*
///
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setUpParametreWindow();

    interfaceCourante = "parametre";

    grille = new Grille();
    feu = new Feu();
    train = new Train();
}

///
/// \fn  MainWindow::setUpParametreWindow()
/// \brief MainWindow::setUpParametreWindow
/// \details Crée les widgets pour quand la MainWindow est en mode paramatre
///
void MainWindow::setUpParametreWindow()
{
    list_widget_parametre_window = new QWidget*[5];

    QPushButton *jouer = new QPushButton("jouer ! ", this);
    jouer->move(600, 500);

    QLabel *niv = new QLabel("Choisir le niveau ", this);
    niv->move(100, 350);
    niv->setFixedWidth(200);

    // On créer le groupe de radioButton pour la selection du niveau
    QWidget *selectNiv = new QWidget(this);
    selectNiv->setGeometry(100, 400, 300, 50);

    QRadioButton *niv1 = new QRadioButton("Facile", selectNiv);
    niv1->setChecked(true);
    QRadioButton *niv2 = new QRadioButton("Difficile", selectNiv);
    niv2->move(100, 0);

    QLabel *vitesse = new QLabel("Choisir la vitesse du train ", this);
    vitesse->move(100, 450);
    vitesse->setFixedWidth(200);


    //On créer le groupe de widget pour la selection de la vitesse
    QWidget *selectVitesse = new QWidget(this);
    selectVitesse->setGeometry(100, 500, 300, 50);


    QRadioButton *vitesse1 = new QRadioButton("Lent", selectVitesse);
    vitesse1->setChecked(true);
    QRadioButton *vitesse2= new QRadioButton("Modéré", selectVitesse);
    QRadioButton *vitesse3 = new QRadioButton("Rapide", selectVitesse);
    vitesse2->move(100, 0);
    vitesse3->move(200, 0);

    // liste pour stocker les widget de la l'interface
    list_widget_parametre_window[0] = jouer;
    list_widget_parametre_window[1] = niv;
    list_widget_parametre_window[2] = vitesse;
    list_widget_parametre_window[3] = selectNiv;
    list_widget_parametre_window[4] = selectVitesse;

    QObject::connect(jouer, SIGNAL(clicked()), this, SLOT(button_jouer_clicked()));
    QObject::connect(niv1, SIGNAL(clicked()), this, SLOT(selectionnerNiv1()));
    QObject::connect(niv2, SIGNAL(clicked()), this, SLOT(selectionnerNiv2()));

    QObject::connect(vitesse1, SIGNAL(clicked()), this, SLOT(selectionnerVit1()));
    QObject::connect(vitesse2, SIGNAL(clicked()), this, SLOT(selectionnerVit2()));
    QObject::connect(vitesse3, SIGNAL(clicked()), this, SLOT(selectionnerVit3()));
}
///
/// \fn MainWindow::~MainWindow()
/// \brief destructeur de Mainwindow
///
MainWindow::~MainWindow()
{
    delete ui;
}
///
/// \fn MainWindow::on_button_aide_clicked()
/// \brief MainWindow::on_button_aide_clicked
///
void MainWindow::on_button_aide_clicked()
{
    Aide a(this);
    a.exec();
}
///
/// \fn MainWindow::placerTrainDepart()
/// \brief MainWindow::placerTrainDepart
///
void MainWindow::placerTrainDepart()
{
    int tPixTrain = 0.3*taillePixelGrille/tailleGrille;

    // permet de centrer en y la train par rapport au case
    int yTrain = (taillePixelGrille/tailleGrille - tPixTrain)/2 + posGrille->y();
    // permet de placer le train juste au bord
    int xTrain = posGrille->x()-tPixTrain;

    train = new Train(QPoint(xTrain,yTrain), QPoint(tPixTrain, tPixTrain));
}
///
/// \fn MainWindow::button_jouer_clicked()
/// \brief MainWindow::button_jouer_clicked
///
void MainWindow::button_jouer_clicked()
{
    grille = new Grille(*posGrille, taillePixelGrille, tailleGrille);

    placerTrainDepart();

    switchAffichage();
}
///
/// \fn MainWindow::switchAffichage()
/// \brief MainWindow::switchAffichage
/// \permet de passer de l'interface configuration a l'interface Partie et inversement
///
void MainWindow::switchAffichage()
{
    if (interfaceCourante == "parametre")
        interfaceCourante = "partie";
    else
        interfaceCourante = "parametre";
    repaint();
}
///
/// \fn MainWindow::paintEvent(QPaintEvent *e)
/// \brief MainWindow::paintEvent
/// \param e: QPaintEvent*
///
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
///
/// \fn  MainWindow::afficherTchou(QPainter *painter) const
/// \brief MainWindow::afficherTchou
/// \param painter: QPainter*
///
void MainWindow::afficherTchou(QPainter *painter) const{
    QPixmap *pixmap= new QPixmap(":/images/petitTrain.jpg");
    painter->drawPixmap(200,30, 450, 300,*pixmap);
}
///
/// \fn MainWindow::afficherFeu()
/// \brief MainWindow::afficherFeu
///
void MainWindow::afficherFeu()
{
    QPainter *painter = new QPainter(this);
    feu->afficher(painter);
    delete painter;
}
///
/// \fn MainWindow::afficherTrain()
/// \brief MainWindow::afficherTrain
///
void MainWindow::afficherTrain()
{
    QPainter *painter = new QPainter(this);
    train->afficher(painter);
    delete painter;
}
///
/// \fn MainWindow::affichePartie()
/// \brief MainWindow::affichePartie
///
void MainWindow::affichePartie()
{
    QPainter *painter = new QPainter(this);


    bool interfac=true;

    if (interfaceCourante =="parametre")
    {
        interfac = true;
        afficherTchou(painter);
    }
    else
    {
        interfac = false;
        afficherFleche(painter);
        afficherGrille();
        //afficherFleche(painter);
        //afficherTchou(painter);
    }
    ui->centralwidget->setVisible(!interfac);
    for (int i=0; i<5; i++){
        this->list_widget_parametre_window[i]->setVisible(interfac);
    }

    delete painter;
}
///
/// \fn MainWindow::afficherFleche(QPainter* painter) const
/// \brief MainWindow::afficherFleche
/// \param painter: QPainter*
///
void MainWindow::afficherFleche(QPainter* painter) const
{
    int tC = taillePixelGrille/tailleGrille;
    int tPixFleche = 0.5*tC;

    // permet de centrer en y la train par rapport au case
    int yFleche = (taillePixelGrille/tailleGrille - tPixFleche)/2 + posGrille->y();
    // permet de placer le train juste au bord
    int xFleche = posGrille->x()-tPixFleche;

    painter->drawPixmap(xFleche, yFleche, tPixFleche, tPixFleche, QPixmap(":/images/fleche.svg"));
    painter->drawPixmap(xFleche + taillePixelGrille + tPixFleche, yFleche+tC*(tailleGrille-1), tPixFleche, tPixFleche, QPixmap(":/images/fleche.svg"));
}
///
/// \fn MainWindow::selectionnerNiv1()
/// \brief MainWindow::selectionnerNiv1
///
void MainWindow::selectionnerNiv1()
{
    ui->label_4->setText("Partie de TchouTchou niveau facile");
    tailleGrille = 2;
}
///
/// \fn MainWindow::selectionnerNiv2()
/// \brief MainWindow::selectionnerNiv2
///
void MainWindow::selectionnerNiv2()
{
    ui->label_4->setText("Partie de TchouTchou niveau difficile");
    tailleGrille = 3;
}
///
/// \fn MainWindow::selectionnerVit1()
/// \brief MainWindow::selectionnerVit1
///
void MainWindow::selectionnerVit1()
{
    vitesseTrain = 1;
}
///
/// \fn MainWindow::selectionnerVit2()
/// \brief MainWindow::selectionnerVit2
///
void MainWindow::selectionnerVit2()
{
    vitesseTrain = 2;
}
///
/// \fn MainWindow::selectionnerVit3()
/// \brief MainWindow::selectionnerVit3
///
void MainWindow::selectionnerVit3()
{
    vitesseTrain = 4;
}
///
/// \fn MainWindow::afficherGrille()
/// \brief MainWindow::afficherGrille
///
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
///
/// \fn MainWindow::mousePressEvent(QMouseEvent *me)
/// \brief MainWindow::mousePressEvent
/// \param me: QMouseEvent*
///
void MainWindow::mousePressEvent(QMouseEvent *me)
{
    if (interfaceCourante == "partie")
        deplacerCase(me);
}
///
/// \fn MainWindow::deplacerCase(QMouseEvent *me)
/// \brief MainWindow::deplacerCase
/// \param me: QMouseEvent*
///
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
///
/// \fn
/// \brief MainWindow::on_buttonDemarrerTrain_clicked
///
void MainWindow::on_buttonDemarrerTrain_clicked()
{
    QString s = grille->verifierChemin();
    qDebug() << s;

    bool valide = (s[0]=='1');
    feu->allumer(valide);
    repaint();
    roulerTrain(s,vitesseTrain);
}
///
/// \fn MainWindow::roulerTrain(QString direction, int v)
/// \brief MainWindow::roulerTrain
/// \param direction: liste dont le 1er caractere indique si le chemin est valide et contenant la liste des instructions de deplacements
/// \param v: taille du pas de deplacement du train
///
void MainWindow::roulerTrain(QString direction, int v)
{
    // taille d'une case
    int tPixCase = taillePixelGrille/tailleGrille;
    // taille en pixel du train
    int tPixTrain = train->getTaillePix().x();
    // permet de centrer en y la train par rapport au case
    int yTrain = (tPixCase - tPixTrain)/2 + posGrille->y();
    // permet de centrer en y la train par rapport au case
    //int xTrain = (tPixCase - tPixTrain)/2 + posGrille->x();
    int xTrain = posGrille->x();
    // Si le train peut aller sur la première case on le met au milieu dessus

    int k=0;
    int inter=20; //nombre de subdivision du pas du train
    //on teste si le train peut commencer a avancer

    if (direction.size() > 1){
        //on positionne le train sur le départ
        train->setPosition(QPoint(xTrain, yTrain));
        repaint();
        //on ajoute la direction de l'arrivee pour ne pas avoir de probleme a l'anticiper
        //seulement si le trajet est bon
        if(direction[0]=='1') direction=direction+'d';
        qDebug() <<"voyage"<< direction;
        //Debut de la trajectoire du train
        if(direction[1]=='d'){
            //on commence à rouler tout droit
            qDebug() << "DEBUT:rail droit";
            for (int j = 1; j < inter; ++j)
            {
                this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                qDebug() << inter;
                qDebug() << v*v*inter;


                train->rouler('d',tPixCase/(inter));
                repaint();
            }
        }
        else{
            //on va effectuer une trajectoire courbe pour epouser la forme du rail
             qDebug() << "DEBUT:rail courbe("<<direction[0]<<",d)";
            for (int j = 1; j < inter/2; ++j)
            {
                this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                k=j;
                //on se déplace selon l'axe de la premiere direction
                //train->rouler('d',tPixCase/(inter));
                train->rouler('d',6*tPixCase/(5*inter));
                //on se deplace dans l'axe de la 2 eme direction
                //train->rouler(direction[1],tPixCase/(inter));//on anticipe le futur déplacemnt
                train->rouler(direction[1],k*k*tPixCase/(inter*20));
                repaint();
            }
        }
        //on fait bouger le train case par case
        for (int i = 1; i < direction.size()-1; ++i)
        {
            //pour toutes cases, on commence par avancer dans la direction indiquee
            qDebug() << "test direction"<<i;
            if(direction[i]==direction[i+1]){
                //on continue si on suit la meme direction que precedemment
                qDebug() << "rail droit";
                for (int j = 1; j < inter; ++j)
                {
                    this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                    train->rouler(direction[i],tPixCase/(inter));
                    repaint();
                }
            }
            //on va effectuer une trajectoire courbe pour epouser la forme du rail
            else{
                 qDebug() << "rail courbe("<<direction[i]<<","<<direction[i+1]<<")";
                for (int j = 1; j < inter/2; ++j)
                {
                    this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                    //on calcule le prochain point pour approximer une courbe
                    k=j;

                    //on se déplace selon l'axe de la premiere direction
                    //train->rouler(direction[i],tPixCase/(inter));
                    train->rouler(direction[i],6*tPixCase/(7*inter));
                    //on se deplace dans l'axe de la 2 eme direction
                    //train->rouler(direction[i+1],tPixCase/(inter));//on anticipe le futur déplacemnt
                    train->rouler(direction[i+1],k*k*tPixCase/(inter*20));
                    repaint();
                     qDebug() << k;
                }
            }
        }
        //si le chemin est valide on deplace le train un cran de plus pour atteindre l'arrivee
        if (direction[0]=='1')
        {
             qDebug() << "on sort";
            for (int j = 1; j < inter/4; ++j)
            {
                qDebug() << j;
                this_thread::sleep_for(chrono::milliseconds(1000/(inter*v*v)));
                train->rouler('d',tPixCase/inter);
                repaint();
            }
        }

    }
    afficherResultat(direction[0].digitValue());
}
///
/// \fn MainWindow::on_Retour_clicked()
/// \brief MainWindow::on_Retour_clicked
///
void MainWindow::on_Retour_clicked()
{
    switchAffichage();
}
///
/// \fn MainWindow::afficherResultat(int g)
/// \brief MainWindow::afficherResultat
/// \param g: 1 si le chemin est valide, 0 sinon
///
void MainWindow::afficherResultat(int g){
    //on teste si le joueur a gagné
    bool res = false;
    if (g==1)
        res = true;

    int action;
    Resultat r(res, this);
    r.exec();

    action = r.getAction();

    if (action ==0)
        this->close();

    else if (action == 1)
    {
        feu->eteindre();
        placerTrainDepart();
    }
    else if (action == 2)
        switchAffichage();

    repaint();
}
