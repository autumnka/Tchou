#include "mainwindow.h"
#include "configuration.h"

#include <QApplication>
///
/// \fn main(int argc, char *argv[])
/// \brief qMain
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
