#include "resultat.h"
#include "ui_resultat.h"

Resultat::Resultat(QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
{
    ui->setupUi(this);
}

Resultat::Resultat(bool gagne, QWidget *parent) : QDialog(parent), ui(new Ui::Resultat)
{
    ui->setupUi(this);

    m_gagne = gagne;

}

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


Resultat::~Resultat()
{
    delete ui;
}
