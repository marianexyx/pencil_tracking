#include "mainwindow.h"
#include <QApplication>
#include "xmlreader.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmlReader xmlReader1;
    MainWindow w(&xmlReader1);
    w.show();

    return a.exec();
}
