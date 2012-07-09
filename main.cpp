#include <QApplication>
#include "mainwindow.h"
#include <QCleanlooksStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new QCleanlooksStyle());
    MainWindow w;
    w.show();

    return a.exec();
}
