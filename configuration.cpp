#include "configuration.h"
#include "ui_configuration.h"



Configuration::Configuration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::on_pushButton_clicked(int argc, char *argv[])
{
    *b = new QApplication
    MainWindow w;
    w.show();
    //return a.exec();
}
