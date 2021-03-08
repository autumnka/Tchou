#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMainWindow>
#include <QApplication>

#include "mainwindow.h"

namespace Ui {
class Configuration;
}

class Configuration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Configuration(QWidget *parent = nullptr);
    ~Configuration();

private slots:
    void on_pushButton_clicked(int argc, char *argv[]);

private:
    Ui::Configuration *ui;
    QApplication *b;
};

#endif // CONFIGURATION_H
