#include "aide.h"
#include "ui_aide.h"
///
/// \fn Aide::Aide(QWidget *parent) :QDialog(parent),ui(new Ui::Aide)
/// \brief Constructeur d'Aide
/// \param parent
///
Aide::Aide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aide)
{
    ui->setupUi(this);

    QPixmap *m_image=new QPixmap("chemin d'accès") ;
    QLabel *m_label=new QLabel(this) ;
    m_label->setPixmap(*m_image) ;
    m_label->move(10,10) ;
}
///
/// \fn Aide::~Aide()
/// \brief Destructeur d'aide
///
Aide::~Aide()
{
    delete ui;
}
/*
void Aide::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);
}
*/
