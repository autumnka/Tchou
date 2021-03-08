#ifndef AIDE_H
#define AIDE_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

// changement
namespace Ui {
class Aide;
}

class Aide : public QDialog
{
    Q_OBJECT

public:
    explicit Aide(QWidget *parent = nullptr);
    ~Aide();

private:
    Ui::Aide *ui;
};

#endif // AIDE_H
