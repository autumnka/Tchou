///
/// \file aide.h
/// \brief La classe Aide permet de manipuler la fenetre aide
/// \author PAULINEAU Jules,POUILLOT Samuel
/// \version 1.0
/// \date 31/03/2021
///
#ifndef AIDE_H
#define AIDE_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QLabel>


namespace Ui {
class Aide;
}

class Aide : public QDialog
{

    Q_OBJECT

public:
    ///
    /// \brief Aide
    /// \param parent
    ///
    explicit Aide(QWidget *parent = nullptr);
    ~Aide();

private:
    ///
    /// \brief ui
    ///
    Ui::Aide *ui;
};

#endif // AIDE_H
