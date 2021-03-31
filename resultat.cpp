#include "resultat.h"
#include "ui_resultat.h"
///
/// \fn Resultat::Resultat(QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
/// \brief constructeur par defaut de resultat
/// \param parent: QWidget*
///
Resultat::Resultat(QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
{
    ui->setupUi(this);
}
///
/// \fn Resultat::Resultat(bool gagne, QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
/// \brief Constructeur de recopie de resultat
/// \param gagne: 1 si le joueur a gagne, 0 sinon
/// \param parent:QWidget*
///
Resultat::Resultat(bool gagne, QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
{
    ui->setupUi(this);

    m_gagne = gagne;

}
///
/// \fn Resultat::paintEvent(QPaintEvent *e)
/// \brief Resultat::paintEvent
/// \param e:QPaintEvent*
///
void Resultat::paintEvent(QPaintEvent *e)
{
    QPainter *painter = new QPainter(this);

    QPixmap *pixmap;

    if(m_gagne)
    {
        ui->label->setText("Bravo tu as gagné !");
        pixmap = new QPixmap(":/images/minion.jpeg");
        painter->drawPixmap(100, 100, 300, 300, *pixmap);
    }
    else
    {
        ui->label->setText("Mauvais chemin !");
    }

    delete painter;
}

///
/// \fn Resultat::~Resultat()
/// \brief destructeur de resultat
///
Resultat::~Resultat()
{
    delete ui;
}
///
/// \fn Resultat::on_pushButton_quitter_clicked()
/// \brief Resultat::on_pushButton_quitter_clicked
///
void Resultat::on_pushButton_quitter_clicked()
{
    action = 0;
    close();
}
///
/// \fn Resultat::on_pushButton_continuer_clicked()
/// \brief Resultat::on_pushButton_continuer_clicked
///
void Resultat::on_pushButton_continuer_clicked()
{
    action = 1;
    close();
}
///
/// \fn Resultat::on_pushButton_recommencer_clicked()
/// \brief Resultat::on_pushButton_recommencer_clicked
///
void Resultat::on_pushButton_recommencer_clicked()
{
    action = 2;
    close();
}
///
/// \fn Resultat::getAction()
/// \brief Resultat::getAction
/// \return action a effectuer
///
int Resultat::getAction()
{
    return action;
}
