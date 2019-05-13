#include "mainwindow.h"
#include "authentication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Authentication auth;
    auth.show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
